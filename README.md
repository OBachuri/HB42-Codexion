*This project has been created as part of the 42 curriculum by obachuri.*

---

# Codexion - Master the race for resources


This project is part of the 42.fr curriculum.

---

**The task**

Race against time in this thrilling concurrency challenge! Orchestrate
multiple coders competing for limited USB dongles using POSIX threads, mutexes, and
smart scheduling—master resource synchronization before burnout strikes.

One or more *coders* sit in a circular way around one table.
Coder routine contains:
- compile,
- debug,
- refactor.

For *compiling* coder use two USB *dongles* and there are as many dongles as coders. 
Between every two coders is one dongle and to compile coder must take left and right dongles.

After compiling coder frees dongles and starts debugging. 
Once debugging is done, they start refactoring.
After completing the refactoring phase, the coder will immediately attempt to
acquire dongles and start compiling again.

Dongle cooldown - after a coder releases a dongle, the dongle cannot be taken again until *dongle_cooldown* milliseconds have elapsed.

Every coder needs to compile regularly and should never *burn out*. Coders burn out if can`t compile in given time.

Coders do not communicate with each other.

Information of any state change of a coder must be formatted and printed. 


## Compile

```bash
make all
```

## Usage

```bash
# Run with parameters
.\codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```


## Algorithm Design & Implementation


#### Conflict Resolution Strategy

#### Implementation 


## Resources & References

## License

Part of the 42 curriculum project.
