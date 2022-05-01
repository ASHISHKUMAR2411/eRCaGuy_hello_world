This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Select explanations of programs:

1. `coulomb_counter_with_cooperative_multitasking_macro` - this is an _excellent_ example of a **coulomb counter** (energy usage measurer; AKA: battery "fuel" gauge measurement system) to obtain energy in Joules (J), Watt-Hours (Whr), or Kilowatt-Hours (KWhr). 
    1. I have posted this code online here: [Arduino Stack Exchange: Calculating Amp/Hrs of a solar panel](https://arduino.stackexchange.com/a/75937/7727).
    1. It uses my sophisticated `CREATE_TASK_TIMER()` cooperative multi-tasking macro.
    1. I first wrote about this technique starting in 2018 here: [Stack Overflow: How to do **high-resolution, timestamp-based, non-blocking, single-threaded cooperative multi-tasking**](https://stackoverflow.com/a/50032992/4561887)

