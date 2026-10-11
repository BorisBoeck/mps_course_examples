# Microprocessor Systems – Course Examples

This repository contains example projects and starter projects for the course **Microprocessor Systems**.

The examples are intended to support the weekly lectures and labs. They are not complete solutions for the semester project.

---

## Repository Structure

```text
mps_course_examples/
│   
├── starter/
│   └── smart_fan_controller_msp430/│
│
├── mps02_gpio/
│   └── mps_lab02_msp430_blinky/
│   
├── mps03_timer/
│   └── ...
│
├── mps04_interrupt/
│   └── ...
│
└── ...
```

### `mpsxx_yyy/`

Contains small, self-contained projects that demonstrate one specific concept.

Examples:

- GPIO output
- timer operation
- interrupts
- ADC
- PWM
- UART

The example projects are intended for studying, testing and experimentation.

### `starter/`

Contains an initial template for the semester project for either the msp430G2553 or the stm32F3K8 controller.

Starter projects provide a working project structure but intentionally leave parts of the implementation to the students.

---

## Development Environment

The MSP430 examples are developed for:

- **Texas Instruments MSP430G2553**
- **Code Composer Studio**
- **MSP-EXP430G2ET LaunchPad**

Later examples will use the STM32 platform.

---

## Using the Repository

Clone the repository once:

```bash
git clone <repository-url>
```

To obtain new examples during the semester:

```bash
cd mps-course-examples
git pull
```

Do not use this repository for your own semester project.

Your personal project should be stored in a separate repository, for example:

```text
smart-fan-controller/
```

---

## Importing a Project into Code Composer Studio

The example projects are complete CCS projects.

Import the required project as an **existing CCS project**.

When importing, keep the project at its original location inside this repository.

Do not copy the project into the CCS workspace.

Example:

```text
mps_course_examples/
└── mps02_gpio/
 │   └── mps_lab02_msp430_blinky/ 
```

The CCS workspace should only contain references to the projects.

---

## Important

The example projects are designed to demonstrate individual concepts as clearly as possible.

Therefore, some examples may intentionally use a very simple software structure.

Your semester project will gradually use a more structured architecture.

Example:

```text
main.c
   │
   ├── app_init()
   │
   └── app_loop()
```

Later, additional modules for drivers, services and application logic will be introduced.

---

## Semester Project

During the semester, you will develop a **Smart Fan Controller**.

The system will gradually include:

- pushbutton input,
- operating modes,
- timer-based behavior,
- interrupts,
- ADC,
- PWM fan control,
- fan speed measurement,
- temperature sensing,
- communication,
- automatic fan control,
- power management and sustainability aspects.

The project will first be developed using the **MSP430G2553** and later transferred to an **STM32F303K8**.

---

## Git

This repository is maintained by the instructor.

Students normally only need:

```bash
git clone
```

and later:

```bash
git pull
```

For your own Smart Fan Controller repository, additional Git commands will be introduced step by step during the semester.

---

## Note

The examples are provided for educational purposes as part of the Microprocessor Systems course.

Always make sure that you understand the code before integrating concepts into your own project.