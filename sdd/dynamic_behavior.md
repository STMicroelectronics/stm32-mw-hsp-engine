\page dynamic_behavior Dynamic behavior

The following section describes the dynamic behavior of the driver.


# HAL HSP Finite State Machine

@startuml
top to bottom direction

<style>
stateDiagram {
arrow {
  FontSize 9
  LineColor Black
}
}
</style>
state "State 0" as state0
state0 : global_state = RESET

state "Initialized" as stateInit {
   state entry <<inputPin>>

   state "State 1" as state_fw_loaded #LimeGreen
   state_fw_loaded : global_state = FW_LOADED

   state "State 2" as state_plugin_loaded #LimeGreen
   state_plugin_loaded : global_state = PLUGIN_LOADED

   state "State 3" as state_idle #Fuchsia
   state_idle : global_state = IDLE

   state "State 4" as state_buildpl #GoldenRod
   state_buildpl : global_state = PROCLIST_RECORDING

   state "State 5" as state_cnn #lightblue
   state_cnn : global_state = CNN_RUNNING

   state output <<outputPin>>
}

note left of stateInit
<b>Requirement:</b>
  <color red>State 1.1 - the SRAM must be enabled to load the Firmware</color>
  <color red>Question: Is HAL_HSP_INIT must enable both HSPI1EN & SRAM4EN with the directive</color>
  By default the SRAM is enabled !
  <color red>USE_HAL_HSP_CLK_ENABLE_MODEL ?</color>

(1) Change state to IDLE only if all Input Triggers are disabled.
(2) When State is set to INACTIVE, the HAL becomes unavailable.
    The peripheral must be reset by RCC or HW
    The HAL_HSP_DeInit could be call RCC Reset API
end note

state0 --> entry : HSP_CORE_Init
entry --[#LimeGreen]> state_fw_loaded :  \r\
<font color=LimeGreen><b>HSP_CORE_LoadFW</b></font>

state_fw_loaded --[#LimeGreen]> state_plugin_loaded : \r\
<font color=LimeGreen><b>HSP_CORE_LoadPlugins</b></font>

state_fw_loaded --[#LimeGreen]> state_idle : \r\
<font color=LimeGreen><b>HSP_CORE_Boot</b></font>

state_plugin_loaded --[#LimeGreen]> state_idle : \r\
<font color=LimeGreen><b>HSP_CORE_Boot</b></font>

state_idle -l[#Fuchsia]> state_buildpl : \r\
<font color=Fuchsia><b>HSP_PROCLIST_StartRecord</b></font>

state_buildpl --[#GoldenRod]> state_buildpl : \r\
<font color=GoldenRod><b>_HSP_PROCLIST_FctXxxx</b></font>

state_buildpl --[#GoldenRod]> state_idle : \r\
<font color=GoldenRod><b>HSP_PROCLIST_StopRecord</b></font>

state_idle --[#Fuchsia]> state_idle : \r\
<color #LimeGreen><b>HSP_PROCLIST_ConfigEventADC</b></color> \r\
<color #LimeGreen><b>HSP_PROCLIST_ConfigEventStream</b></color>\r\
<color #LimeGreen><b>HSP_PROCLIST_ConfigEventTrigger</b></color> \r\
<color #LimeGreen><b>HSP_PROCLIST_ConfigEventCPU</b></color>\r\
<color #LimeGreen><b>HSP_PROCLIST_ConfigEventSPE</b></color>\r\
<color #LimeGreen><b>HSP_PROCLIST_Run</b></color> \r\
<color #LimeGreen><b>HSP_PROCLIST_TrigSWEvent</b></color>

state_idle --[#Fuchsia]> state_cnn : \r\
<font color=Fuchsia><b>hsp_cnn_Xxxxxx</b></font>

state_cnn --[#lightblue]> state_idle : \r\
<color #lightblue><b>hsp_cnn_Xxxxxx</b></color>

state_idle -l> output: HSP_CORE_DeInit
output -> state0: HSP_CORE_DeInit

@enduml



# state_cnn --[#lightblue]> state_idle : \r\
# <font color=lightblue><b>end of the current hsp_cnn_Xxxx</b></font>
# MW HSP Sequence Diagram

## MW HSP initialization sequence

To start working with the HSP, the user must do the following steps:\n

@startuml

Title MW HSP initialization

participant "<b>User Application</b>" as app
participant "<font color=Fuchsia><b>MW HSP</b></font>" as mw_hsp
participant "<font color=Fuchsia><b>MW IF HSP BRAM</b></font>" as mw_hsp_bram_if
participant "<font color=Fuchsia><b>MW IF HSP HW</b></font>" as mw_hsp_hw_if
participant "<font color=green><b>HAL HSP</b></font>" as hal_hsp

== APP Initialization ==
[o-> app : Hard Reset
app -> hal_cortex : HAL_Init
app <-- hal_cortex
app -> hal_rcc : Configure system clock
app <-- hal_rcc

== HSP System Initialization==
alt#grey #lightgrey If Interrupt needed
app -> cortex : Enable HSPx_IRQn
app <-- cortex
end

app -> rcc : Enable the HSP clock
note right rcc: Does MW_HSP_Init must do it ?
app <-- rcc

opt#grey HSPSRAM is enabled by default
app -> rcc : Enable the HSP SRAM clock
app <-- rcc
end

== MW HSP Init ==
app -> mw_hsp: MW_HSP_Init()
mw_hsp -> mw_hsp_bram_if: HSP_BRAM_IF_Init()
mw_hsp <-- mw_hsp_bram_if
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_Init()
mw_hsp_hw_if -> hal_hsp: HAL_HSP_Init()
note right hal_hsp: Use the HSP instance defined by <b>HSPx</b> in mw_hsp_conf.h
mw_hsp_hw_if <-- hal_hsp
mw_hsp <-- mw_hsp_hw_if

mw_hsp -> mw_hsp: MW_HSP_LoadFW() * Weak function
activate mw_hsp
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_LoadFW_CRAM()
mw_hsp_hw_if -> hal_hsp: HAL_HSP_LoadFW_CRAM()
mw_hsp_hw_if <-- hal_hsp
mw_hsp <-- mw_hsp_hw_if
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_LoadFW_DRAM()
mw_hsp_hw_if -> hal_hsp: HAL_HSP_LoadFW_DRAM()
mw_hsp_hw_if <-- hal_hsp
mw_hsp <-- mw_hsp_hw_if
mw_hsp <-- mw_hsp
mw_hsp -> mw_hsp: MW_HSP_LoadPlugins() * Weak function
opt multiple call available
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_LoadPlugin()
mw_hsp_hw_if -> hal_hsp: HAL_HSP_LoadPlugin()
mw_hsp_hw_if <-- hal_hsp
deactivate mw_hsp
mw_hsp <-- mw_hsp_hw_if
end
mw_hsp <-- mw_hsp
hnote over mw_hsp : global_state = INIT
app <-- mw_hsp: MW_OK

@enduml


== HSP Configuration + Start ==

@enduml

## MW HSP Processing List Recording sequence

@startuml
Title MW HSP Processing List Recording sequence

participant "<b>User Application</b>" as app
participant "<font color=Fuchsia><b>MW HSP</b></font>" as mw_hsp
participant "<font color=Fuchsia><b>MW IF HSP BRAM</b></font>" as mw_hsp_bram_if
participant "<font color=Fuchsia><b>MW IF HSP HW</b></font>" as mw_hsp_hw_if
participant "<font color=green><b>HAL HSP</b></font>" as hal_hsp

== Start the recording ==
app -> mw_hsp_hw_if: HSP_HW_IF_PROCLIST_StartRecord(<b><color green>PL_ID</color></b>)
mw_hsp_hw_if -> hal_hsp: HAL_HSP_PROCLIST_ActivateControlSupervisor
mw_hsp_hw_if <-- hal_hsp: HAL_OK
mw_hsp_hw_if -> hal_hsp: HAL_HSP_PROCLIST_SendCommand(<b>HSP_CMD_PRO_CFG_START</b>, ...)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
app <-- mw_hsp_hw_if: MW_HSP_OK

== Call of APIs from ProcList Library ==
group Call of multiple API from ProcList library
opt
app -> mw_hsp: MW_HSP_BRAM_Malloc
mw_hsp -> mw_hsp_bram_if: HSP_BRAM_IF_Malloc
mw_hsp <-- mw_hsp_bram_if
app <-- mw_hsp
end
opt
app -> mw_hsp: MW_HSP_BRAM_SetPopAddress
mw_hsp -> mw_hsp_bram_if: HSP_BRAM_IF_SetPopAddress
mw_hsp <-- mw_hsp_bram_if
app <-- mw_hsp
end
app -> mw_hsp_proclist_lib: MW_HSP_PROCLIST_Xxxxx(...)
app <-- mw_hsp_proclist_lib
note over app, mw_hsp_proclist_lib
During the recording, some processing can be done between 2 calls of Proclist Library to prepare data.
end note
end

== Stop the recording ==
app -> mw_hsp_hw_if: HSP_HW_IF_PROCLIST_StopRecord()
mw_hsp_hw_if -> hal_hsp: HAL_HSP_PROCLIST_SendCommand(<b>HSP_CMD_PRO_CFG_END</b>, ...)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
app <-- mw_hsp_hw_if: MW_HSP_OK

== Configure the event related to the Processing List ID (Optional) ==
note over app, hal_hsp
This configuration step must be done if the execution of a processing list depends of these kind of event:
  - Receive Data from ADC interface
  - Read or Write Data from STREAM interface
  - Trigger from TRGIN interface (DMA Transfer complete...)
  - Trigger from CSEG interface (Action by CPU)
  - Internal from HSEG interface (Action by SPE)
end note
opt
app -> mw_hsp_hw_if: MW_HSP_EVENT_Config(p_config)
note right mw_hsp_hw_if: the configuration is initialized with <b><color green>PL_ID</color></b> as event ID
mw_hsp_hw_if -> hal_hsp: HAL_HSP_EVENT_Config(...)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
app <-- mw_hsp_hw_if: MW_HSP_OK
end

@enduml


## MW HSP Run Processing List by Event or "manually"

@startuml
Title MW HSP Run Processing List by Event or "manually"

participant "<b>User Application</b>" as app
participant "<font color=Fuchsia><b>MW HSP</b></font>" as mw_hsp
participant "<font color=Fuchsia><b>MW IF HSP BRAM</b></font>" as mw_hsp_bram_if
participant "<font color=Fuchsia><b>MW IF HSP HW</b></font>" as mw_hsp_hw_if
participant "<font color=green><b>HAL HSP</b></font>" as hal_hsp

== Enable Events related to execute processing list by Event ==
note over app, hal_hsp: each selected event must be config by MW_HSP_Event_Config
app -> mw_hsp: MW_HSP_EVENT_Enable(mask of event)
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_EVENT_Enable(mask of event)
mw_hsp_hw_if -> hal_hsp: HAL_HSP_EVENT_Enable(mask of event)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
mw_hsp <-- mw_hsp_hw_if: IF_OK
app <-- mw_hsp

== Trig a CPU Event to execute the processing list linked to CSEG event ==
note over app, hal_hsp: The event related to the processing list must be config with CSEG as trigger source
app -> mw_hsp: MW_HSP_EVENT_SWTrig(mask of event)
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_EVENT_SWTrig(mask of event)
mw_hsp_hw_if -> hal_hsp: HAL_HSP_EVENT_SWTrig(mask of event)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
mw_hsp <-- mw_hsp_hw_if: IF_OK
app <-- mw_hsp: MW_HSP_OK

== Run a Processing list in Lowest Priority ==
note over app, mw_hsp: For asynchronous execution, set the timeout parameter to <color red>0</color>.
app -> mw_hsp: MW_HSP_PROCLIST_Run(<b>PL_ID</b>, <b><color red>0</color></b>)
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_PROCLIST_Run(<b>PL_ID</b>, <b><color red>0</color></b>)
mw_hsp_hw_if -> hal_hsp: HAL_HSP_PROCLIST_Run(<b>PL_ID</b>, <b><color red>0</color></b>)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
mw_hsp <-- mw_hsp_hw_if: IF_OK
app <-- mw_hsp: MW_HSP_OK

note over app, mw_hsp
For synchron execution, set the timeout parameter with a value higher than <color red>0</color>.
If the timeout value is set to 0xFFFFFFFF (like HAL_MAX_DELAY), the function is blocking.
end note

app -> mw_hsp: MW_HSP_PROCLIST_Run(<b>PL_ID</b>, <b><color red>1000</color></b>)
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_PROCLIST_Run(<b>PL_ID</b>, <b><color red>1000</color></b>)
mw_hsp_hw_if -> hal_hsp: HAL_HSP_PROCLIST_Run(<b>PL_ID</b>, <b><color red>1000</color></b>)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
mw_hsp <-- mw_hsp_hw_if: IF_OK
app <-- mw_hsp: MW_HSP_OK

== Disable Events of processing list ==
app -> mw_hsp: MW_HSP_EVENT_Disable(mask of event)
mw_hsp -> mw_hsp_hw_if: HSP_HW_IF_EVENT_Disable(mask of event)
mw_hsp_hw_if -> hal_hsp: HAL_HSP_EVENT_Disable(mask of event)
mw_hsp_hw_if <-- hal_hsp: HAL_OK
mw_hsp <-- mw_hsp_hw_if: IF_OK
app <-- mw_hsp

@enduml




## MW HSP Run Direct Command

@startuml
Title MW HSP Run Direct Command

participant "<b>User Application</b>" as app
participant "<font color=Fuchsia><b>MW HSP</b></font>" as mw_hsp
participant "<font color=Fuchsia><b>MW IF HSP HW</b></font>" as mw_hsp_hw_if
participant "<font color=green><b>MW HSP Direct LIB</b></font>" as mw_hsp_direct_lib
participant "<font color=green><b>HW HSP</b></font>" as hw_hsp

note over app, hw_hsp: The MW must be initialized

== Run a direct command ==
opt
note over app, mw_hsp: Dynamic Allocation of buffer before calling the HSP Processing Function
app -> mw_hsp: MW_HSP_BRAM_Malloc(...)
app <-- mw_hsp:
end
note over app, mw_hsp_direct_lib: For synchro usecase, the Application must enable the Preprocessing Directive 
alt #LightBlue <b>Asynchronous mode</b>
app -> mw_hsp_direct_lib: MW_HSP_DIRECT_RFFT(...)
mw_hsp_direct_lib -> hw_hsp: Write command directly to DCMDIDR register access
mw_hsp_direct_lib <-- hw_hsp
mw_hsp_direct_lib -> mw_hsp_direct_lib: MW_HSP_Direct_RFFT
note over mw_hsp_direct_lib, hw_hsp : HSP Register Write access
mw_hsp_direct_lib <-- mw_hsp_direct_lib: MW_HSP_Direct_RFFT
app <-- mw_hsp_direct_lib
else #Pink <b>Synchronous mode (USE_MW_HSP_DIRECT_COMMAND_SYNCHRONOUS)</b>
app -> mw_hsp_direct_lib: MW_HSP_DIRECT_RFFT(...)
mw_hsp_direct_lib -> hw_hsp: Write command directly to DCMDIDR register access
mw_hsp_direct_lib <-- hw_hsp
mw_hsp_direct_lib -> mw_hsp_direct_lib: MW_HSP_Direct_RFFT
note over mw_hsp_direct_lib, hw_hsp : HSP Register Write access
mw_hsp_direct_lib <-- mw_hsp_direct_lib: MW_HSP_Direct_RFFT

mw_hsp_direct_lib -> mw_hsp_hw_if: HSP_HW_IF_WaitEndOfDirectCommand()
...Waiting time depend of Processing List complexity...
mw_hsp_direct_lib <-- mw_hsp_hw_if

app <-- mw_hsp_direct_lib
end
@enduml



## MW HSP Run DSP function

@startuml
Title MW HSP Run DSP Function

participant "<b>User Application</b>" as app
participant "<font color=Fuchsia><b>MW HSP</b></font>" as mw_hsp
participant "<font color=Fuchsia><b>MW IF HSP HW</b></font>" as mw_hsp_hw_if
participant "<font color=green><b>MW HSP DSP LIB</b></font>" as mw_hsp_dsp_lib
participant "<font color=green><b>HW HSP</b></font>" as hw_hsp

note over app, hal_hsp: The MW must be initialized

== Run a DSP function ==
opt
note over app, mw_hsp: Dynamic Allocation of buffer before calling the HSP Processing Function
app -> mw_hsp: MW_HSP_BRAM_Malloc(...)
app <-- mw_hsp:
end

app -> mw_hsp_dsp_lib: stm32_hsp_fir_f32(...)
mw_hsp_dsp_lib -> hw_hsp: Write command directly to DCMDIDR register access
mw_hsp_dsp_lib <-- hw_hsp
mw_hsp_dsp_lib -> mw_hsp_dsp_lib: HSP_Direct_Fir
note over mw_hsp_dsp_lib, hw_hsp : HSP Register Write access
mw_hsp_dsp_lib <-- mw_hsp_dsp_lib

mw_hsp_dsp_lib -> mw_hsp_hw_if: HSP_HW_IF_WaitEndOfDirectCommand()
...Waiting time depend of Processing List complexity...
mw_hsp_dsp_lib <-- mw_hsp_hw_if

app <-- mw_hsp_dsp_lib

@enduml




## Driver usage: Polling on All Expected Output Flags
@startuml
Title Driver usage: Polling on All Expected Output Flags

' To add a number by line
'autonumber

' Fix order of each column
participant "<b>User Application</b>" as app
participant "<font color=green><b>HAL HSP</b></font>" as hal_hsp
participant "<font color=green><b>HW HSP</b></font>" as hw_hsp

Note over app, hal_hsp#lightgreen: The HSP driver has already been initialized and configured.
hnote over app : global_state=ACTIVE

== Usecase without timeout ==
Note over app, hal_hsp#lightyellow: Usecase where the 2 flags are triggered
app -> hal_hsp: HAL_HSP_OUTPUT_PollFlag(HAL_HSP_POLL_MODE_ALL, HAL_HSP_FLAG_LEOUTD2 | HAL_HSP_FLAG_LEOUTR8)

activate hal_hsp
hal_hsp -> hal_hsp: Poll on both flags
hal_hsp <-- hw_hsp: FLAG_LEOUTD2 <:26a1:>
hal_hsp -> hal_hsp: <&reload>
hal_hsp <-- hw_hsp: FLAG_LEOUTR8 <:26a1:>
deactivate hal_hsp
hal_hsp -> hw_hsp: clear FLAG_LEOUTD2 | HAL_HSP_FLAG_LEOUTR8

app <-- hal_hsp: HAL_OK

== Usecase with timeout ==
Note over app, hal_hsp#lightyellow: Usecase where one flag is triggered on time
app -> hal_hsp: HAL_HSP_OUTPUT_PollFlag(HAL_HSP_POLL_MODE_ALL, HAL_HSP_FLAG_LEOUTD2 | HAL_HSP_FLAG_LEOUTR8)

activate hal_hsp
hal_hsp -> hal_hsp: Poll on both flags
hal_hsp <-- hw_hsp: FLAG_LEOUTR8 <:26a1:>

app <-- hal_hsp: HAL_TIMEOUT
deactivate hal_hsp

hal_hsp <-- hw_hsp: FLAG_LEOUTD2 <:26a1:>
@enduml

## Usecase Multithread context: Critical section for SetSWINLevel[_IT]
@startuml
Title Usecase Multithread context: Critical section for SetSWINLevel[_IT]

box "Application" #Pink
participant "<b>Thread 1</b>" as t1
participant "<b>Thread 2</b>" as t2
end box

box "HAL HSP" #LightBlue
    participant "<font color=green><b>entrance from t1</b></font>" as driver_play_t1
    participant "<font color=green><b>entrance from t2</b></font>" as driver_play_t2
end box

box "Hardware" #LightGrey
participant "IP HSP" as hw_hsp
end box

Note over t1, hw_hsp#lightyellow
This diagram shows a Critical Section for write access on SWIN register.
This usecase is the same for API SetFlagTransition for write access to FLCTL register.
end note
== Usecase: Call simultaneously SetSWINLevel (Polling mode with internal loop on WWBFS)  ==

t1 --> driver_play_t1: HAL_HSP_SetSWINLevel
hnote right : SWINWBFS set to 0 by HW

t2 --> driver_play_t2: HAL_HSP_SetSWINLevel

group#Red Critical Section identify
loop While SWINWBFS flag == 1
activate driver_play_t2
driver_play_t2 -> hw_hsp: Read SWINWBFS flag status

activate driver_play_t1
loop While SWINWBFS flag == 1
driver_play_t1 --> hw_hsp: Read SWINWBFS flag status
driver_play_t1 <-- hw_hsp: status (0 or 1)
end loop
driver_play_t2 <-- hw_hsp: status (0 or 1)
end loop

driver_play_t2 -> hw_hsp: Write to SWIN register
hnote right : SWINWBFS set to 1 by HW

activate hw_hsp
driver_play_t2 <-- hw_hsp: <font color=blue>Write in progress</font>
driver_play_t1 -> hw_hsp: Write to SWIN register
driver_play_t1 <-- hw_hsp: <font color=red><b>Write ignored</b></font>
end group

loop While SWINWBFS flag == 1
driver_play_t2 -> hw_hsp: read SWINWBFS flag status
driver_play_t2 <-- hw_hsp: SWINWBFS flag status (0 or 1)
end loop

loop While SWINWBFS flag == 1
driver_play_t1 -> hw_hsp: read SWINWBFS flag status
driver_play_t1 <-- hw_hsp: SWINWBFS flag status (0 or 1)
end loop

hw_hsp --> hw_hsp: <font color=green><b>Write Complete (WC flag set to 1 and WBFS reset to 0)</b></font>
hnote right : SWINWBFS set to 0 by HW

driver_play_t2 <-- hw_hsp: SWINWBFS = 0
driver_play_t1 <-- hw_hsp: SWINWBFS = 0
deactivate hw_hsp

group#Red HAL returns HAL_OK but the write is wrong !
t1 <-- driver_play_t1: <font color=red><b>HAL_OK (even if the write is ignored)</b></font>
end group

t2 <-- driver_play_t2: HAL_OK

note over driver_play_t1, driver_play_t2 : Implementation with a polling on WBFS flag instead of WC.
@enduml

## Usecase:  SetSWINLevel[_IT] using a special State in handle
@startuml
Title SetSWINLevel[_IT] using a special State in handle

box "Application" #Pink
participant "<b>Thread 1</b>" as t1
participant "<b>Thread 2</b>" as t2
end box

box "HAL HSP" #LightBlue
    participant "<font color=green><b>entrance from t1</b></font>" as driver_play_t1
    participant "<font color=green><b>entrance from t2</b></font>" as driver_play_t2
end box

box "Hardware" #LightGrey
participant "IP HSP" as hw_hsp
end box

Note over t1, hw_hsp#lightyellow
This diagram shows a Critical Section for write access on SWIN register.
This usecase is the same for API SetFlagTransition for write access to FLCTL register.
end note
== Usecase: Call simultaneously SetSWINLevel (Polling mode with internal loop on WWBFS)  ==
note over Application First call of SetSWINLevel/_IT

t1 --> driver_play_t1: HAL_HSP_SetSWINLevel
hnote over IP HSP : SWINWBFS set to 0 by HW

t2 --> driver_play_t2: HAL_HSP_SetSWINLevel

group#Red Critical Section identify
loop While SWINWBFS flag == 1
activate driver_play_t2
driver_play_t2 -> hw_hsp: Read SWINWBFS flag status

activate driver_play_t1
loop While SWINWBFS flag == 1
driver_play_t1 --> hw_hsp: Read SWINWBFS flag status
driver_play_t1 <-- hw_hsp: status (0 or 1)
end loop
driver_play_t2 <-- hw_hsp: status (0 or 1)
end loop

driver_play_t2 -> hw_hsp: Write to SWIN register
hnote right : SWINWBFS set to 1 by HW

activate hw_hsp
driver_play_t2 <-- hw_hsp: <font color=blue>Write in progress</font>
driver_play_t1 -> hw_hsp: Write to SWIN register
driver_play_t1 <-- hw_hsp: <font color=red><b>Write ignored</b></font>
end group

loop While SWINWBFS flag == 1
driver_play_t2 -> hw_hsp: read SWINWBFS flag status
driver_play_t2 <-- hw_hsp: SWINWBFS flag status (0 or 1)
end loop

loop While SWINWBFS flag == 1
driver_play_t1 -> hw_hsp: read SWINWBFS flag status
driver_play_t1 <-- hw_hsp: SWINWBFS flag status (0 or 1)
end loop

hw_hsp --> hw_hsp: <font color=green><b>Write Complete (WC flag set to 1 and WBFS reset to 0)</b></font>
hnote right : SWINWBFS set to 0 by HW

driver_play_t2 <-- hw_hsp: SWINWBFS = 0
driver_play_t1 <-- hw_hsp: SWINWBFS = 0
deactivate hw_hsp

group#Red HAL returns HAL_OK but the write is wrong !
t1 <-- driver_play_t1: <font color=red><b>HAL_OK (even if the write is ignored)</b></font>
end group

t2 <-- driver_play_t2: HAL_OK

note over driver_play_t1, driver_play_t2 : Implementation with a polling on WBFS flag instead of WC.
@enduml


@startuml
participant "<b>Thread 1</b>" as t1
participant "<b>Thread 2</b>" as t2
box "HAL HSP" #LightBlue
    participant "<font color=green><b>entrance from t1</b></font>" as driver_play_t1
    participant "<font color=green><b>entrance from t2</b></font>" as driver_play_t2
end box

participant "IP HSP" as periph_play

== Usecase: Call simultaneously SetSWINLevel (Polling mode with internal loop on WC)  ==
t1 --> driver_play_t1: HAL_HSP_SetSWINLevel
t2 --> driver_play_t2: HAL_HSP_SetSWINLevel
driver_play_t2 --> periph_play: read SWINWBFS flag
driver_play_t1 --> periph_play: read SWINWBFS flag
driver_play_t1 <-- periph_play: 0
driver_play_t2 <-- periph_play: 0
driver_play_t2 --> periph_play: Write to SWIN register
note right : SWINWBFS set to 1 by HW
activate periph_play
loop until SWINWC == 1 or timeout
driver_play_t2 --> periph_play: read SWINWC
driver_play_t2 <-- periph_play
end
note right : SWINWBFS is reset to 0 by HW when Write is completed
deactivate periph_play
driver_play_t1 --> periph_play: Write to SWIN register

t2 <-- driver_play_t2: HAL_OK

driver_play_t1 <-- periph_play: <font color=red><b>Write ignored</b></font>
t1 <-- driver_play_t1: <font color=red><b>HAL_OK (even if the write is ignored)</b></font>

t1 --> driver_play_t1: HAL_HSP_SetSWINLevel
driver_play_t1 --> periph_play: read SWINWBFS
driver_play_t1 <-- periph_play: 0
driver_play_t1 --> periph_play: Write to SWIN register
activate periph_play
loop until SWINWC == 1 or timeout
driver_play_t1 --> periph_play: read SWINWC
driver_play_t1 <-- periph_play
end

deactivate periph_play
t1 <-- driver_play_t1: HAL_OK

note over driver_play_t1, driver_play_t2 : Implementation with a polling on SWINWC flag.
@enduml

## Usecase: Secure only HSP configuration registers access
@startuml
title <font size=18><b>Usecase: Secure only HSP configuration registers access</b></font>

box "Application" #Pink
participant "<b>App NS</b>" as app_ns
participant "<b>App S</b>" as app_s
end box

box "HSP" #LightGreen
participant "<font color=green><b>HAL HSP</b></font>" as hal_hsp
participant "<font color=green><b>HW HSP</b></font>" as hw_hsp
end box

box "NVIC" #LightGrey
participant "<font color=grey><b>HW NVIC</b></font>" as hw_nvic
participant "<font color=grey><b>HSP_S IRQ Handler</b></font>" as play_s_irqhandler
participant "<font color=green><b>HSP_NS IRQ Handler</b></font>" as play_ns_irqhandler
end box

hnote over hw_hsp: CFGCR_UNLOCK = 1

== Secure HSP Configuration Registers ==
note over app_s, hw_hsp: The Secure Application configures the HSP Attributes to secure only Config Registers
hnote over app_s: global_state == RESET
app_s -> hal_hsp: HAL_HSP_Init with HSP Secure handle
app_s <-- hal_hsp: HAL_OK
hnote over app_s: global_state == INIT

== HSP Configuration & Start ==
note over app_s, hw_hsp
Call of SetConfig APIs to configure the peripheral
(HAL_HSP_INPUT_SetConfig / HAL_HSP_LUT_SetConfig() / HAL_HSP_OUTPUT_SetConfig())
end note
hnote over app_s: global_state == IDLE

app_s -> hal_hsp : HAL_HSP_Start()
hal_hsp -> hw_hsp: lock the config
hal_hsp <-- hw_hsp
hnote over hw_hsp: CFGCR_UNLOCK = 0
hnote over app_s: global_state == ACTIVE
app_s <-- hal_hsp : HAL_OK

== Run the Non-Secure Application ==
app_s -> app_ns: run non-secure application

== Non Secure part - Start the HSP ==

hnote over app_ns: global_state == RESET
app_ns -> hal_hsp: HAL_HSP_Init with HSP Non Secure handle
hal_hsp -> hw_hsp : Read Lock Status
note over hal_hsp, hw_hsp: Reading a secure register from NS Application will always returned 0
hal_hsp <-- hw_hsp: 0 means the config is locked !
app_ns <-- hal_hsp: HAL_OK
hnote over app_ns: global_state == ACTIVE

opt configuration Edge Trigger for some LE Output (Flag transition)
app_ns -> hal_hsp: HAL_HSP_OUTPUT_SetEdgeTrigger
app_ns <-- hal_hsp: HAL_OK
end

opt Use of SWIN
app_ns -> hal_hsp: HAL_HSP_SWIN_Write
app_ns <-- hal_hsp: HAL_OK
end

opt Use of LE Output ITs
app_ns -> hal_hsp: HAL_HSP_OUTPUT_EnableIT
app_ns <-- hal_hsp: HAL_OK
app_ns -> hal_hsp: HAL_HSP_OUTPUT_DisableIT
app_ns <-- hal_hsp: HAL_OK
end

== HSP Interrupts ==
hw_nvic -> play_ns_irqhandler : <&flash>execute IRQ Handler
play_ns_irqhandler -> app_ns: call of NS callbacks
play_ns_irqhandler <-- app_ns
hw_nvic <-- play_ns_irqhandler

@enduml

@startuml
title <font size=18><b>Usecase: Full Secure HSP registers access</b></font>
participant "<b>Program Non Secure</b>" as prog_ns
participant "<b>Program Secure</b>" as prog_s
participant "<b>HAL HSP</b>" as driver_play
participant "<b>HSP1_S_IRQ_Handler</b>" as irq_handler_s

== From Secure: HSP configuration with default callbacks ==
prog_s -> driver_play: HAL_HSP_Init
prog_s <-- driver_play: HAL_OK
note right: HSP bus clock is enabled and optionally the play kernel clock
prog_s -> driver_play: HAL_HSP_ConfigAttributes
prog_s <-- driver_play: HAL_OK
note right: Configure Secure access for All HSP registers
note over prog_s, driver_play: Configure Inputs, Logic Elements & Outputs
prog_s -> driver_play: HAL_HSP_Lock
prog_s <-- driver_play: HAL_OK

prog_s -> prog_ns: Call <b>Non Secure main</b> function
== From Non-Secure: Using HSP with default callbacks ==
note over prog_ns
   Forbidden to call HAL_HSP_Init !
   Any call of HSP HAL Driver will generate illegal access
end note

note over prog_ns
   Use Non-Secure Callable (NSC) APIs provided by Secure application in "secure_nsc.h" interface
   example:
       SECURE_RegisterCallback
       SECURE_[Set/Get]FlagTransition
       SECURE_[Set/Get]SWINLevel
end note

opt Logic Element Output Flag Transition triggered calling a NS callback
prog_ns -> prog_s: SECURE_RegisterCallback
note right: Register a callback from Non-Secure
prog_ns <-- prog_s
irq_handler_s -> prog_s: HAL_HSP_LEOutputStatusCallback
prog_s -> prog_ns: ns_leoutputstatus_callback
prog_s <-- prog_ns
irq_handler_s <-- prog_s
end

opt Change SWIN Level with a Non-Secure callable
prog_ns -> prog_s: SECURE_SetSWINLevel
activate prog_s
prog_s -> prog_s: check input parameters
prog_s -> driver_play: HAL_HSP_SetSWINLevel
prog_s <-- driver_play: HAL_OK
prog_ns <-- prog_s

end
@enduml

@startuml
title <font size=18><b>Usecase: Low power consumption with only HSP config part in Secure</b></font>
participant "<b>Program Non Secure</b>" as prog_ns
participant "<b>Program Secure</b>" as prog_s
participant "<b>HAL HSP</b>" as driver_play
participant "<b>RCC</b>" as periph_rcc

== From Secure: HSP configuration with default callbacks ==
prog_s -> driver_play: HAL_HSP_Init
prog_s <-- driver_play: HAL_OK
note right: HSP bus clock is enabled and optionally the play kernel clock
prog_s -> driver_play: HAL_HSP_ConfigAttributes
prog_s <-- driver_play: HAL_OK
note right: Configure Secure access for All HSP registers
note over prog_s, driver_play: Configure Inputs, Logic Elements & Outputs
prog_s -> driver_play: HAL_HSP_Lock
prog_s <-- driver_play: HAL_OK

group disable HSP1 to reduce Power consumption
prog_s -> periph_rcc: CLEAR_BIT(RCC_CCIPR3, HSP1APBEN)\nCLEAR_BIT(RCC_CCIPR3, HSP1EN)
note right
   The bitfield RCC_CCIPR3_HSP1APBEN is only accessible from Secure part.
   Then, only RCC_CCIPR3_HSP1EN is accessible from non-secure part.
end note
prog_s <-- periph_rcc
end group

prog_s -> prog_ns: Call <b>Non Secure main</b> function
== From Non-Secure: Using HSP with default callbacks ==
note over prog_ns
   Forbidden to call HAL_HSP_Init !
end note

group Action to use HSP
prog_ns -> periph_rcc: SET_BIT(RCC_CCIPR3, HSP1EN)
note right: Enable HSP1
prog_ns <-- periph_rcc

note over prog_ns
   Use HAL HSP driver excepted Configuration APIs
end note

prog_ns -> periph_rcc: CLEAR_BIT(RCC_CCIPR3, HSP1EN)
note right: Disable HSP1 to reduce Power Consumption
prog_ns <-- periph_rcc

end

@enduml



## WakeUp from Low Power Stop WFI (Mustang H5-4M)
@startuml
' To add a number by line
'autonumber
Title WakeUp from Low Power Stop with Wait For Interrupt(WFI) (Mustang H5-4M)
' Fix order of each column
participant "<b>User Application</b>" as p1
participant "<font color=green><b>HSP</b></font>" as p2
participant "<b>EXTI</b>" as p3
participant "<b>RCC</b>" as p4
participant "<b>PWR</b>" as p5
participant "<b>SCB</b>" as p6
participant "<b>Cortex</b>" as p7
participant "<b>NVIC</b>" as p8

Note over p2#lightgreen: The HSP driver has already been initialized and configured.

== Program Configuration ==
note over p1, p8 : Configure NVIC.
p1 -> p8 : Enable HSP IRQ & configure priority
p1 <-- p8:

note over p1, p2 : Configure HSP Output 14.
p1 -> p2 : Enable IT on LE Output x
p1 <-- p2:

p1 -> p2 : Configure source of Output Multiplexer 14 to LE Output x
p1 <-- p2:

note over p1, p3 : Configure the EXTI line.
p1 -> p3 : Disable WakeUp line from Event\n\
         SET_BIT(EMR3, EXTI_EMR3_EM64)
p1 <-- p3:

p1 -> p3 : Enable WakeUp line from IT and also trig an EXTI IT for HSP\n\
         SET_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:

p1 -> p3 : Configure WakeUp Event Trigger on Rising Edge\n\
         SET_BIT(RTSR3, EXTI_RTSR3_RT64)
p1 <-- p3:

note over p1, p4 : Enable Low Power HSP clock.
p1 -> p4: SET_BIT(APB3LPENR, RCC_APB3LPENR_HSP1LPEN)
p1 <-- p4:

== HSP Entering in LowPower with WFI ==

p1 -> p5 : CLEAR_BIT(PMCR, PWR_PMCR_LPMS);
p1 <-- p5:

p1 -> p6: SET_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))

p1 -> p7: Wait For Interrupt Request: __WFI()

== Wakeup Time ==
p2 -> p3: <&flash> HSP IT trigger
p3 -> p7: Wakeup
p3 -> p8: EXTI IT

p8 -> p1: execute HSP_IRQ_Handler
activate p1

p1 -> p2: Check & Clear HSP Output Flag x
activate p1
p1 <-- p2:
p1 -> p1: Execute HAL_HSP LEOutputStatus callback
p1 --> p1:
deactivate p1

note over p1, pp3 : Access to EXTI register to read & clear flag (To implement if possible)
p1 -> p3: Check & Clear EXTI line Pending Flag (RTSR register) (ex RPIF64 for H5-4M)
activate p1

p1 <-- p3:
p1 -> p1: Execute HAL_HSP Wakeup callback
p1 --> p1:
p1 --> p3: End of IRQHandler

deactivate p1

deactivate p1

== Exiting from LowPower STOP Mode ==
p1 <-- p7: Exit from LP
p1 -> p6: CLEAR_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 <-- p6:

@enduml

## WakeUp from Low Power Stop "WFE" (with "ORed" HSP_IT & EXTI line)
@startuml
' To add a number by line
'autonumber
title WakeUp from Low Power Stop "WFE" (with "ORed" HSP_IT & EXTI line)

' Fix order of each column
participant "<b>User Application</b>" as p1
participant "<font color=green><b>HSP</b></font>" as p2
participant "<b>EXTI</b>" as p3
participant "<b>RCC</b>" as p4
participant "<b>PWR</b>" as p5
participant "<b>SCB</b>" as p6
participant "<b>Cortex</b>" as p7
participant "<b>NVIC</b>" as p8

Note over p2#lightgreen: The HSP driver has already been initialized and configured.

== Program Configuration ==
note over p1, p2 : Configure HSP Output 14.
p1 -> p2 : Configure source of Output Multiplexer 14 to LE Output x
p1 <-- p2:

note over p1, p3 : Configure the HSP EXTI line on Event.

p1 -> p3 : Enable WakeUp line from Event\n\
         SET_BIT(EMR3, EXTI_EMR3_EM64)
p1 <-- p3:
p1 -> p3 : Disable WakeUp line from Interrupt to avoid to set the pending flag if HSP_IT enabled !\n\
         CLEAR_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:

p1 -> p3 : Configure WakeUp Event on Rising Edge\n\
         SET_BIT(RTSR3, EXTI_RTSR3_RT64)
p1 <-- p3:

note over p1, p4 : Enable Low Power HSP clock.
p1 -> p4: SET_BIT(APB3LPENR, RCC_APB3LPENR_HSP1LPEN)
p1 <-- p4:

== HSP Entering in LowPower with WFE ==

p1 -> p5 : CLEAR_BIT(PMCR, PWR_PMCR_LPMS);
p1 <-- p5:

p1 -> p6: SET_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 -> p7: __SEV()
p1 -> p7: Wait For Event : __WFE()
p1 -> p7: Wait For Event : __WFE()

== Wakeup Time ==
p2 -> p3: <&flash> HSP Event on output 14
p3 -> p7: Wakeup
p3 -> p8: <&flash> HSP_IT (NS or S)
p8 -> p1: execute HSP_IRQ_Handler (NS or S)
activate p1
p1 -> p3: <font color=blue><b>Read status of EXTI HSP Wake Up Line Flag</b></font>
p1 <-- p3
activate p1
note right: "Case flag is set"
p1 -> p3: <font color=blue><b>Clear EXTI Wake Up Pending flag</b></font>
p1 <-- p3
p1 -> p1: <font color=blue><b>execute Wakeup callback</b></font>
deactivate p1
p8 <-- p1
deactivate p1

== Exiting from LowPower STOP Mode ==
p1 <-- p7: Exit from LP
p1 -> p6: CLEAR_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 <-- p6:

@enduml

## WakeUp from Low Power Stop "WFE" (with "ORed" HSP_IT & EXTI line)
@startuml
' To add a number by line
'autonumber
title WakeUp from Low Power Stop "WFE" (with "ORed" HSP_IT & EXTI line)

' Fix order of each column
participant "<b>User Application</b>" as p1
participant "<font color=green><b>HSP</b></font>" as p2
participant "<b>EXTI</b>" as p3
participant "<b>RCC</b>" as p4
participant "<b>PWR</b>" as p5
participant "<b>SCB</b>" as p6
participant "<b>Cortex</b>" as p7
participant "<b>NVIC</b>" as p8

Note over p2#lightgreen: The HSP driver has already been initialized and configured.

== Program Configuration ==
note over p1, p2 : Configure HSP Output 14.
p1 -> p2 : Configure source of Output Multiplexer 14 to LE Output x
p1 <-- p2:

note over p1, p3 : Configure the HSP EXTI line on Event.

p1 -> p3 : Enable WakeUp line from Event\n\
         SET_BIT(EMR3, EXTI_EMR3_EM64)
p1 <-- p3:
p1 -> p3 : Disable WakeUp line from Interrupt to avoid to set the pending flag if HSP_IT enabled !\n\
         CLEAR_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:

p1 -> p3 : Configure WakeUp Event on Rising Edge\n\
         SET_BIT(RTSR3, EXTI_RTSR3_RT64)
p1 <-- p3:

note over p1, p4 : Enable Low Power HSP clock.
p1 -> p4: SET_BIT(APB3LPENR, RCC_APB3LPENR_HSP1LPEN)
p1 <-- p4:

== HSP Entering in LowPower with WFE ==

p1 -> p5 : CLEAR_BIT(PMCR, PWR_PMCR_LPMS);
p1 <-- p5:

p1 -> p6: SET_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 -> p7: __SEV()
p1 -> p7: Wait For Event : __WFE()
p1 -> p7: Wait For Event : __WFE()

== Wakeup Time ==
p2 -> p3: <&flash> HSP Event on output 14
p3 -> p7: Wakeup
p3 -> p8: <&flash> HSP_IT (NS or S)
p8 -> p1: execute HSP_IRQ_Handler (NS or S)
activate p1
p1 -> p3: <font color=blue><b>Read status of EXTI HSP Wake Up Line Flag</b></font>
p1 <-- p3
activate p1
note right: "Case flag is set"
p1 -> p3: <font color=blue><b>Clear EXTI Wake Up Pending flag</b></font>
p1 <-- p3
p1 -> p1: <font color=blue><b>execute Wakeup callback</b></font>
deactivate p1
p8 <-- p1
deactivate p1

== Exiting from LowPower STOP Mode ==
p1 <-- p7: Exit from LP
p1 -> p6: CLEAR_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 <-- p6:

@enduml

## WakeUp from Low Power Stop "WFE" from Mustang H5-4M
@startuml
' To add a number by line
'autonumber
title WakeUp from Low Power Stop "WFE" from Mustang H5-4M

' Fix order of each column
participant "<b>User Application</b>" as p1
participant "<font color=green><b>HSP</b></font>" as p2
participant "<b>EXTI</b>" as p3
participant "<b>RCC</b>" as p4
participant "<b>PWR</b>" as p5
participant "<b>SCB</b>" as p6
participant "<b>Cortex</b>" as p7
participant "<b>NVIC</b>" as p8

Note over p2#lightgreen: The HSP driver has already been initialized and configured.

== Program Configuration ==
note over p1, p2 : Configure HSP Output 14.
p1 -> p2 : Configure source of Output Multiplexer 14 to LE Output x
p1 <-- p2:

note over p1, p3 : Configure the HSP EXTI line on Event.

p1 -> p3 : Enable WakeUp line from Event\n\
         SET_BIT(EMR3, EXTI_EMR3_EM64)
p1 <-- p3:

alt
note over p1, p3 : Disabled EXTI IMR Line to avoid that the pending flag is set and an EXT_IT i trigger to HSP IRQ.
p1 -> p3 : Disable WakeUp line from Interrupt to avoid to set the pending flag if HSP_IT enabled !\n\
         CLEAR_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:

else

note over p1, p3 : Disabled EXTI IMR Line to avoid that the pending flag is set and an EXT_IT i trigger to HSP IRQ.
p1 -> p3 : Disable WakeUp line from Interrupt to avoid to set the pending flag if HSP_IT enabled !\n\
         CLEAR_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:
end alt

p1 -> p3 : Configure WakeUp Event on Rising Edge\n\
         SET_BIT(RTSR3, EXTI_RTSR3_RT64)
p1 <-- p3:

note over p1, p4 : Enable Low Power HSP clock.
p1 -> p4: SET_BIT(APB3LPENR, RCC_APB3LPENR_HSP1LPEN)
p1 <-- p4:

== HSP Entering in LowPower with WFE ==

p1 -> p5 : CLEAR_BIT(PMCR, PWR_PMCR_LPMS);
p1 <-- p5:

p1 -> p6: SET_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 -> p7: __SEV()
p1 -> p7: Wait For Event : __WFE()
p1 -> p7: Wait For Event : __WFE()

== Wakeup Time ==
p2 -> p3: <&flash> HSP Event on output 14
p3 -> p7: Wakeup

== HSP IRQ process if IMR3 enabled (TBC) ==
p3 -> p8: <&flash> HSP_IT (NS or S)
p8 -> p1: execute HSP_IRQ_Handler (NS or S)
activate p1
p1 -> p3: <font color=blue><b>Read status of EXTI HSP Wake Up Line Flag</b></font>
p1 <-- p3
activate p1
note right: "Case flag is set"
p1 -> p3: <font color=blue><b>Clear EXTI Wake Up Pending flag</b></font>
p1 <-- p3
p1 -> p1: <font color=blue><b>execute Wakeup callback</b></font>
deactivate p1
p8 <-- p1
deactivate p1

== Exiting from LowPower STOP Mode ==
p1 <-- p7: Exit from LP
p1 -> p6: CLEAR_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 <-- p6:

@enduml


## WakeUp from Low Power Stop "WFE" with "ORed" on HSP_IT & EXTI_WakeUp_HSP_Line
@startuml
' To add a number by line
'autonumber
title WakeUp from Low Power Stop "WFE" with "ORed" on HSP_IT & EXTI_WakeUp_HSP_Line

' Fix order of each column
participant "<b>User Application</b>" as p1
participant "<font color=green><b>HSP</b></font>" as p2
participant "<b>EXTI</b>" as p3
participant "<b>RCC</b>" as p4
participant "<b>PWR</b>" as p5
participant "<b>SCB</b>" as p6
participant "<b>Cortex</b>" as p7
participant "<b>NVIC</b>" as p8

Note over p2#lightgreen: The HSP driver has already been initialized and configured.

== Program Configuration ==
note over p1, p2 : Configure HSP Output 14.
p1 -> p2 : Configure source of Output Multiplexer 14 to LE Output x
p1 <-- p2:

note over p1, p3 : Configure the HSP EXTI line on Event.

p1 -> p3 : Enable WakeUp line from Event\n\
         SET_BIT(EMR3, EXTI_EMR3_EM64)
p1 <-- p3:
p1 -> p3 : Disable WakeUp line from Interrupt to avoid to set the pending flag if HSP_IT enabled !\n\
         CLEAR_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:

opt
note over p1, p3 : Disabled EXTI IMR Line to avoid that the pending flag is set and an EXT_IT i trigger to HSP IRQ.
p1 -> p3 : Disable WakeUp line from Interrupt to avoid to set the pending flag if HSP_IT enabled !\n\
         CLEAR_BIT(IMR3, EXTI_IMR3_IM64)
p1 <-- p3:

end opt

p1 -> p3 : Configure WakeUp Event on Rising Edge\n\
         SET_BIT(RTSR3, EXTI_RTSR3_RT64)
p1 <-- p3:

note over p1, p4 : Enable Low Power HSP clock.
p1 -> p4: SET_BIT(APB3LPENR, RCC_APB3LPENR_HSP1LPEN)
p1 <-- p4:

== HSP Entering in LowPower with WFE ==

p1 -> p5 : CLEAR_BIT(PMCR, PWR_PMCR_LPMS);
p1 <-- p5:

p1 -> p6: SET_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 -> p7: __SEV()
p1 -> p7: Wait For Event : __WFE()
p1 -> p7: Wait For Event : __WFE()

== Wakeup Time ==
p2 -> p3: <&flash> HSP Event on output 14
p3 -> p7: Wakeup
p3 -> p8: <&flash> HSP_IT (NS or S)
p8 -> p1: execute HSP_IRQ_Handler (NS or S)
activate p1
p1 -> p3: <font color=blue><b>Read status of EXTI HSP Wake Up Line Flag</b></font>
p1 <-- p3
activate p1
note right: "Case flag is set"
p1 -> p3: <font color=blue><b>Clear EXTI Wake Up Pending flag</b></font>
p1 <-- p3
p1 -> p1: <font color=blue><b>execute Wakeup callback</b></font>
deactivate p1
p8 <-- p1
deactivate p1

== Exiting from LowPower STOP Mode ==
p1 <-- p7: Exit from LP
p1 -> p6: CLEAR_BIT(SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk))
p1 <-- p6:

@enduml



===================== Cube 1 part ================================
@startuml

Title HAL HSP initialization from Hardware Reset (Cube1)

participant "<b>User Application</b>" as app
participant "<font color=green><b>HAL HSP</b></font>" as hal_hsp
participant "HW HSP" as hw_hsp
participant "HAL CORTEX\n(NVIC)" as hal_cortex
participant "HAL RCC" as hal_rcc

== HAL Initialization ==
[o-> app : Hard Reset
app -> hal_cortex : HAL_Init
app <-- hal_cortex
app -> hal_rcc : Configure system clock
app <-- hal_rcc

== HSP Load the Firmware & Plugins ==
app -> hal_rcc: HAL_RCC_HSPRAM_EnableClock()
app <-- hal_rcc
app -> HSP_SRAM: upload part of Firmware in CRAM
app <-- HSP_SRAM:
app -> HSP_SRAM: upload part of Firmware in DRAM
app <-- HSP_SRAM:

opt
app -> HSP_SRAM: upload part of Plugin in CRAM (consecutively)
app <-- HSP_SRAM:
app -> HSP_SRAM: upload part of Plugin in DRAM (consecutively)
app <-- HSP_SRAM:
end

== HAL HSP Initialization ==
opt If HAL_HSP_MspInit does not enable the HSP Bus Clock
app -> hal_rcc: HAL_RCC_HSP_EnableClock()
app <-- hal_rcc
end

hnote over hw_hsp: CR_CDRLCK = 0 (Free access to CRAM & DRAM)

app -> hal_hsp : HAL_HSP_Init
hnote over hw_hsp: HSP_CR.BOOTEN = 0
hnote over hal_hsp : global_state = INIT

app <-- hal_hsp : HAL_OK

app -> hal_hsp : HAL_HSP_Start
hnote over hw_hsp: HSP_CR.BOOTEN = 1
hnote over hal_hsp : global_state = READY

app <-- hal_hsp : HAL_OK

@enduml


===================== Cube 1 part ================================
@startuml

Title Direct Command Management (Cube1)

participant "<b>User Application</b>" as app
box "Middleware"
participant "<font color=purple><b>HSP CORE</b></font>" as mw_hsp_core
participant "<font color=purple><b>HSP BRAM</b></font>" as mw_hsp_bram
participant "<font color=purple><b>HSP HW</b></font>" as mw_hsp_hw
participant "<font color=purple><b>HSP Direct Lib</b></font>" as mw_hsp_direct_lib
end box
participant "<b>HAL HSP</b>" as hal_hsp
participant "<b>HW HSP</b>" as hw_hsp

== Middleware Initialization ==
app -> mw_hsp_core : HSP_CORE_Init
note over mw_hsp_core, mw_hsp_hw: Init all interfaces
app <-- mw_hsp_core

== Call of Direct Command ==
alt Buffer Allocation in BRAMAB
app -> mw_hsp_bram: <b>HSP_BRAM_Malloc(...)</b>
app <-- mw_hsp_bram
end
app -> mw_hsp_direct_lib: <b>STM32_HSP_DIRECT_RFFT(...)</b>
mw_hsp_direct_lib -> mw_hsp_hw: <b>HSP_HW_IF_WriteDirectCommand(<font color=green>HSP_DIRECT_CMD_RFFT</font>)</b>
note over mw_hsp_hw, mw_hsp_direct_lib: API declared as <b>__STATIC_FORCEINLINE</b>
mw_hsp_direct_lib <-- mw_hsp_hw

mw_hsp_direct_lib -> mw_hsp_direct_lib: HSP_DIRECT_RFFT_WriteParameters(...)
mw_hsp_direct_lib -> mw_hsp_hw: HSP_HW_IF_WriteParameter(...)
mw_hsp_hw -> hal_hsp: HAL_HSP_WriteParameter(...)
note over mw_hsp_hw, hal_hsp #red : API declared as <b>__STATIC_FORCEINLINE</b> with HSP_TypeDef pointer as pointer instead of HAL Handle !!!
mw_hsp_hw <-- hal_hsp
mw_hsp_direct_lib <-- mw_hsp_hw:

mw_hsp_direct_lib -> mw_hsp_hw: HSP_HW_IF_WriteDirectCommandPointerr(...)
mw_hsp_hw -> hal_hsp: HAL_HSP_WriteDirectCommandPointer(...)
note over mw_hsp_hw, hal_hsp #red : API declared as <b>__STATIC_FORCEINLINE</b> with HSP_TypeDef pointer as pointer instead of HAL Handle !!!
mw_hsp_hw <-- hal_hsp
mw_hsp_direct_lib <-- mw_hsp_direct_lib

opt USE_HSP_DIRECT_COMMAND_SYNCHRONOUS = 1
mw_hsp_direct_lib -> mw_hsp_hw: <b>HSP_HW_IF_WaitEndOfDirectCommand()</b>
mw_hsp_direct_lib <-- mw_hsp_hw
end

app <-- mw_hsp_direct_lib


@enduml



===================== Cube 1 part ================================
@startuml

Title STREAM Buffer (Cube1)

participant "<b>User Application</b>" as app
box "Middleware"
participant "<font color=purple><b>HSP CORE</b></font>" as mw_hsp_core
participant "<font color=purple><b>HSP PROCLIST</b></font>" as mw_hsp_proclist
participant "<font color=purple><b>HSP HW</b></font>" as mw_hsp_hw
end box
participant "<b>HAL HSP</b>" as hal_hsp
participant "<b>HW HSP</b>" as hw_hsp

== Middleware Initialization ==
app -> mw_hsp_core : HSP_CORE_Init
note over mw_hsp_core, mw_hsp_hw: Init all interfaces
app <-- mw_hsp_core

==  Record a Processing List triggered on STREAM Buffer 0 RX is full ==
app -> mw_hsp_proclist : HSP_SEQ_StartRecordPL
app <-- mw_hsp_proclist
...
app -> mw_hsp_proclist : HSP_SEQ_STREAM_GetBufferAddress(STREAM_BUFFER_0)
note right: Get STREAM Buffer Address to pass it as parameter of Processing Function
app <-- mw_hsp_proclist
...
app -> mw_hsp_proclist : HSP_SEQ_StopRecordPL
app <-- mw_hsp_proclist

==  Configure STREAM Buffer 0 in RX mode ==
app -> mw_hsp_proclist : HSP_SEQ_EVENT_SetConfig_StreamBuffer()
app <-- mw_hsp_proclist

==  Start the STREAM Buffer 0 by passing the buffer of samples to write ==
app -> mw_hsp_proclist : HSP_SEQ_STREAM_Buffer_Start(STREAM_BUFFER_0, samples_1, SAMPLES_1_SIZE)
app <-- mw_hsp_proclist

==  Record a Processing List triggered on STREAM Buffer 1 RX is full ==
app -> mw_hsp_proclist : HSP_SEQ_StartRecordPL
app <-- mw_hsp_proclist
...
app -> mw_hsp_proclist : HSP_SEQ_STREAM_GetBufferAddress(STREAM_BUFFER_1)
note right: Get STREAM Buffer Address to pass it as parameter of Processing Function
app <-- mw_hsp_proclist
...
app -> mw_hsp_proclist : HSP_SEQ_StopRecordPL
app <-- mw_hsp_proclist

==  Configure STREAM Buffer 1 in RX mode ==
app -> mw_hsp_proclist : HSP_SEQ_EVENT_SetConfig_StreamBuffer()
app <-- mw_hsp_proclist

==  Start the STREAM Buffer 1 by passing the buffer of samples to write ==
app -> mw_hsp_proclist : HSP_SEQ_STREAM_Buffer_Start(STREAM_BUFFER_1, samples_2, SAMPLES_2_SIZE)
app <-- mw_hsp_proclist

==  Start the STREAM  ==
app -> mw_hsp_proclist : HSP_SEQ_STREAM_Enable()
app <-- mw_hsp_proclist

==  STREAM Buffer Processing  ==
hw_hsp -> hal_hsp: HAL_HSP_IRQHandler()
hal_hsp -> mw_hsp_hw: HSP_HW_IF_STREAM_BufferEmptyCallback
mw_hsp_hw -> hal_hsp: HAL_HSP_STREAM_WriteBuffer(STREAM_BUFFER_0)
mw_hsp_hw <-- hal_hsp
mw_hsp_hw <--> mw_hsp_hw: Decrement number of samples_1 to 1
opt
note over mw_hsp_hw, hal_hsp: Disable STREAM BUFFER 0 IT when counter reachs 0
end
mw_hsp_hw -> hal_hsp: HAL_HSP_STREAM_WriteBuffer(STREAM_BUFFER_1)
mw_hsp_hw <-- hal_hsp
mw_hsp_hw <--> mw_hsp_hw: Decrement number of samples_2 to 1
opt
note over mw_hsp_hw, hal_hsp: Disable STREAM BUFFER 1 IT when counter reachs 0
end

note over mw_hsp_hw, hal_hsp: STREAM BUFFER 1 can be finished before STREAM_BUFFER 0


@enduml