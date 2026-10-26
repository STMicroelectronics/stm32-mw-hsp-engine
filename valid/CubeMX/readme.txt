Reference Usecase of CubeMX Code Generation for Middleware HSP

mx_usecase_acc_1: All Default Value
	Mode: Accelerator
	Static allocation: None
	MW Init Config: Default Value
		HSP Performance = Disabled (Default)                 (hsp_conf.h: HSP_PERFORMACE_MONITOR 0U)
		Direct Command Synchronous Mode = Enabled  (Default) (hsp_conf.h: HSP_PERFORMACE_MONITOR 1U)
		HSP_BRAM_AI_SIZE = 0U (Default)                      (hsp_conf.h: HSP_BRAM_AI_SIZE 0U)
	MW Processing List Config: None
	
mx_usecase_acc_2: HSP Performance enabled
	Mode: Accelerator
	Static allocation: None
	MW Init Config:
		HSP Performance = Enabled                           (hsp_conf.h: HSP_PERFORMACE_MONITOR 1U) 
		Direct Command Synchronous Mode = Enabled (Default) (hsp_conf.h: HSP_PERFORMACE_MONITOR 1U)
	MW Processing List Config: None
	
mx_usecase_acc_3:
	Mode: Accelerator
	Static allocation: None
	MW Init Config:
		HSP Performance = Disabled (Default)       (hsp_conf.h: HSP_PERFORMACE_MONITOR 0U)
		Direct Command Synchronous Mode = Disabled (hsp_conf.h: HSP_PERFORMACE_MONITOR 0U)
	MW Processing List Config: None

mx_usecase_acc_4:
	Mode: Accelerator
	Static allocation: None
	MW Init Config:
		HSP Performance = Enabled                  (hsp_conf.h: HSP_PERFORMACE_MONITOR 1U)
		Direct Command Synchronous Mode = Disabled (hsp_conf.h: HSP_PERFORMACE_MONITOR 0U)
		
	MW Processing List Config: None

mx_usecase_acc_5:
	Mode: Accelerator
	Static allocation: None
	MW Init Config:
		HSP Performance = Disabled (Default)                 (hsp_conf.h: HSP_PERFORMACE_MONITOR 0U)
		Direct Command Synchronous Mode = Enabled  (Default) (hsp_conf.h: HSP_PERFORMACE_MONITOR 1U)
		HSP_BRAM_AI_SIZE = 1024                              (hsp_conf.h: HSP_BRAM_AI_SIZE 1024U)
		
	MW Processing List Config: None

mx_usecase_acc_6: All Default Value + IRQ Enable
	Mode: Accelerator
	Static allocation: None
	MW Init Config: Default Value
	MW Processing List Config: None
	stm32u3xx_it.c & .h files are updates
		HSP1_IRQHandler is declared
		HSP1_IRQHandler contains the call of the 3 MW HSP IRQ Handler functions

mx_usecase_acc_7: SmartClocking Disable All
	Mode: Accelerator
	Static allocation: None
	MW Init Config: Default Value
		Add a call to MW to disable the 3 clocks
	MW Processing List Config: None

mx_usecase_acc_8: MMC SmartClocking Disabled & BRAM Arbitration & Lock registers
	Mode: Accelerator
	Static allocation: None
	MW Init Config: Default Value
		Add a call to MW to disable the MMC SmartClocking
		Add a call to MW to configure BRAM Arbitrations HSP_BRAM_ARBITRATION_LATENCY_8_CYCLES
		Add a call to MW to lock the config
	MW Processing List Config: None

mx_usecase_seq_1:
	Mode: Sequencer
	Static allocation:
		float my_var1
	MW Init Config: Default Value
	MW Processing List Config:
		PL_ID 1
			ScalarIAdd_f32(&my_var1, 1.0f, &my_var1)

mx_usecase_seq_1:
	Mode: Sequencer
	Static allocation: 
		float my_var1
	MW Init Config: Default Value
	MW Processing List Config:
		PL_ID 1
			ScalarIAdd_f32(&my_var1, 1.0f, &my_var1)

mx_usecase_seq_2:
	Mode: Sequencer
	Static allocation: 
		float my_var1
		float inBuffer[512]
		float outBuffer[1024]
	MW Init Config: Default Value
	MW Processing List Config:
		PL_ID 34 (No Event) - PL name : MY_PROCLIST_USER_34
			ScalarIAdd_f32(&my_var1, 1.0f, &my_var1)
		PL_ID 1 (Event CSEG) - PL name : MY_PROCLIST_USER_1
			ScalarIAdd_f32(&inBuffer, 1.0f, &outBuffer)

mx_usecase_seq_3: TRGIN Event 12 & 5
	Mode: Sequencer
	Static allocation: 
		float my_var1
		float inBuffer[512]
		float outBuffer[1024]
	MW Init Config: Default Value
	MW Processing List Config:
		Event 2:
		 	HSP_POLARITY_RISING
  			HSP_DMA1_CHANNEL9_TC
  			TRGIN[4]
  			Synchro = HSP_CORE_TASK_NONE
		Event 5:
		 	HSP_POLARITY_FALLING
  			HSP_TIM3_TRGO
  			TRGIN[7]
  			Synchro = HSP_CORE_TASK_NONE


mx_usecase_seq_3: STREAM Event 3 & 6
	Mode: Sequencer
	Static allocation: 
		float my_var1
		float inBuffer[512]
		float outBuffer[1024]
	MW Init Config: Default Value
	MW Processing List Config:
		Integer to float: Enabled
		Event 3:
		 	STREAM[2]
  			direction: CPU to HSP
  			Synchro = HSP_CORE_TASK_NONE
		Event 6:
			STREAM[1]
  			direction: HSP to CPU
  			Synchro = HSP_CORE_TASK_NONE