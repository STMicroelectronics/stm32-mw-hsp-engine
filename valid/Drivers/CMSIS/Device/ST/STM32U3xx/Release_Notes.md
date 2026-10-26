---
pagetitle: Release Notes for STM32U3xx CMSIS
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for <mark>STM32U3xx CMSIS</mark>
Copyright &copy; 2024 STMicroelectronics\

[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# Purpose

This driver provides the CMSIS device for the STM32U3xx product. This covers 

- STM32U375xx devices
- STM32U385xx devices

This driver is composed of the description of the registers under "Include" directory.

Various template files are provided to easily build an application. They can be adapted to fit applications requirements.

- Templates/system_stm32u3xx.c contains the initialization code referred as SystemInit.
- Startup files are provided as example for EWARM&copy;, MDK-ARM&copy;, STM32CubeIDE&copy;.
- Linker files are provided as example for EWARM&copy;, MDK-ARM&copy;, STM32CubeIDE&copy;.

:::


::: {.col-sm-12 .col-lg-8}
# Update history
::: {.collapse}
<input type="checkbox" id="collapse-section3" checked aria-hidden="true">
<label for="collapse-section3" aria-hidden="true"> __V1.2.0 / 04-June-2025__ </label>
<div>

## Maintenance Release

- Maintenance release of CMSIS for **STM32U3xx** firmware package supporting **STM32U385xx/STM32U375xx** devices

## Contents
- Add PKA on STM32U375xx
- Add CCB sanity check feature on STM32U385xx
- Swap bit position FLASH MEM and FLASH REG in GTZC1 TZIC registers

## Known Limitations

- None

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section2"  aria-hidden="true">
<label for="collapse-section2" aria-hidden="true"> __V1.1.0 / 05-February-2025__ </label>
<div>

## Maintenance Release

- Maintenance release of CMSIS for **STM32U3xx** firmware package supporting **STM32U385xx/STM32U375xx** devices

## Contents
- Fix PWR_I3CPUCR2_PG14_I3CPU_Pos value
- Suppress unused bit
- Minor fix on comments

## Known Limitations

- None

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1"  aria-hidden="true">
<label for="collapse-section1" aria-hidden="true"> __V1.0.0 / 30-October-2024__ </label>
<div>

## First Release

- First official release of CMSIS for **STM32U3xx** firmware package supporting **STM32U385xx/STM32U375xx** devices

## Contents

- First official release of CMSIS devices drivers
  - Support of STM32U385xx/STM32U375xx devices

## Known Limitations

- None

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.1">Info</abbr>
:::
:::
</footer>
