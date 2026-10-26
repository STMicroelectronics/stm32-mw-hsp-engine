\page component_diagram Component diagram

# PLAY Component Diagram

@startuml
<style>
componentDiagram {
   arrow {
      FontSize 8
   }
}
</style>

title HSP Software Component Diagram .h Inclusion
package "Modules" {
    package "Firmware" {
        [stm32_hsp_fw_def_generic.h]
        [stm32_hsp_fw_ram_generic.h]
    }
    package "Proclist_lib" {
        [stm32_hsp_proclist_conditional.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_crc.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_fir.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_matrix.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_memory.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_scalar.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_transform.h] --> [stm32_hsp_proclist_def.h] : #include
        [stm32_hsp_proclist_vector.h] --> [stm32_hsp_proclist_def.h] : #include
    }
    package "cnn_lib" {
        [stm32_hsp_cnn.h] #SkyBlue
    }
    package "dsp_lib" {
        [stm32_hsp_dsp.h] #SkyBlue
    }
    package "direct_lib" {
        [stm32_hsp_direct_command.h] #SkyBlue
    }

    [stm32_hsp_modules_def.h] --> [stm32_hsp_direct_command.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_dsp.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_cnn.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_conditional.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_crc.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_fir.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_matrix.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_memory.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_scalar.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_transform.h] : #include
    [stm32_hsp_modules_def.h] --> [stm32_hsp_proclist_vector.h] : #include
}

package "Core" {
    [stm32_hsp.h] -up-> [stm32_hsp_def.h] : #include
    [stm32_hsp.h] --> [stm32_hsp_core.h] : #include
    [stm32_hsp.h] --> [stm32_hsp_bram.h] : #include
    [stm32_hsp.h] --> [stm32_hsp_proclist.h] : #include
}

package "Config" {
    [stm32_hsp_conf.h]
    [stm32_hsp_if_conf.h]
}

package "Interfaces" {
    [hsp_bram_if.h] -d-> [interface.h] : #include
    [hsp_hw_if.h] -d-> [interface.h] : #include
}

[stm32_hsp_def.h] --> [stm32_hsp_fw_def_generic.h] : #include
[stm32_hsp.h] --> [stm32_hsp_modules_def.h] : #include
[stm32_hsp.h] --> [stm32_hsp_conf.h] : #include
[stm32_hsp_proclist.h] --> [hsp_hw_if.h] : #include

[stm32_hsp_cnn.h] --> [stm32_hsp_def.h] : #include
[stm32_hsp_direct_command.h] --> [stm32_hsp_def.h] : #include
[stm32_hsp_direct_command.h] --> [stm32_hsp_conf.h] : #include
[stm32_hsp_dsp.h] --> [stm32_hsp_direct_command.h] : #include
[stm32_hsp_proclist_def.h] --> [stm32_hsp_def.h] : #include


[hsp_hw_if.h] -up-> [stm32_hsp_if_conf.h]
[hsp_bram_if.h] -up-> [stm32_hsp_def.h]

@enduml

