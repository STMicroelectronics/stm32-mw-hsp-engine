\page component_diagram Component diagram

# HSP Component Diagram

@startuml
<style>
componentDiagram {
   arrow {
      FontSize 8
   }
}
</style>

title HSP Software Component Diagram

package "Middleware STM32_HSP" {
    [HSP_CORE_SERVICE] #SkyBlue
    [HSP_HW_BRAM_IF] #SkyBlue
    [HSP_HW_IF] #SkyBlue
}

package "HAL" {
    [HAL_SERVICE]
    [HAL_HSP] #SkyBlue
    [HAL_RCC]
}

package "Low Layer" {
    [CMSIS]
    [HSP Interrupt routine service]
    [LL_BUS]
}

package "HW" {
    [STM32_HW]
}

[Appli] --> [HSP_CORE_SERVICE] : STM32 HSP API
[HSP_CORE_SERVICE] --> [HSP_HW_BRAM_IF]: BRAM Management
[HSP_CORE_SERVICE] --> [HSP_HW_IF]: HSP Management
[HSP_HW_IF] --> [HAL_HSP]: Call
[HSP_HW_BRAM_IF] --> [HAL_HSP]: Get BRAM HW Data (Address & Size)
[Appli] --> [HAL_HSP] : HAL HSP API
[Appli] <-- [HAL_HSP] : HSP callback
[HAL_HSP] --> [LL_BUS] : EnableClock & IsEnabledClock APIs
[HAL_HSP] -r-> [HAL_RCC] : HAL_RCC_HSP_GetKernelClkFreq
[HAL_HSP] -l-> [HAL_SERVICE] : HAL_GetTick
[HAL_HSP] <-- [HSP Interrupt routine service]

[HAL_HSP] --> [CMSIS] : HSP register def
[STM32_HW] -u--> [HSP Interrupt routine service] : HSPx IRQ
[STM32_HW] <-u--> [HAL_HSP] : HSP registers R/W
@enduml