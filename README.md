# Speedhack
Fork of [Speedhack](https://github.com/absoIute/Speedhack) by [absoIute](https://github.com/absoIute)

Lightweight speedhacking source.
A "speedhack" is a way of manipulating the time of a program, usually used in games, it can slow down, speed up or even hault an entire program.

## Usage
To use this, you must have the Detours NuGet installed for the project.
This fork serves as a way to inject this speedhack DLL into a program and use the functions by locating them with `GetProcAddress`. I would suggest loading the DLL into memory of your own program, first, and then subtract the location of each function from the dlls base address, so you can get the offsets.

Once you have injected it into another program, you can call the setup and detach functions with `CreateRemoteThread` and no parameters. To set the speed, you need to write the float value to the target process's memory and call `CreateRemoteThread` with the address of your float as the parameter. Examples below are from a C# application [DS2S META](https://github.com/Nordgaren/DS2S-META).

```cs
	private void GetSpeedhackOffsets(string dllName)
        {
            var lib = Kernel32.LoadLibrary(dllName);
            var setupOffset = Kernel32.GetProcAddress(lib, "Setup").ToInt64() - lib.ToInt64();
            var setSpeedOffset = Kernel32.GetProcAddress(lib, "SetSpeed").ToInt64() - lib.ToInt64();
            var detachOffset = Kernel32.GetProcAddress(lib, "Detach").ToInt64() - lib.ToInt64();
            SetupPtrOffset = (IntPtr)setupOffset;
            SetSpeedPtrOffset = (IntPtr)setSpeedOffset;
            DetachPtrOffset = (IntPtr)detachOffset;
            Free(lib);
        }
	
	public void SetSpeed(float value)
        {
            IntPtr setSpeed = (IntPtr)(SpeedhackDllPtr.ToInt64() + SetSpeedPtrOffset.ToInt64());
            IntPtr valueAddress = GetPrefferedIntPtr(sizeof(float), SpeedhackDllPtr);
            Kernel32.WriteBytes(Handle, valueAddress, BitConverter.GetBytes(value));
            var thread = Kernel32.CreateRemoteThread(Handle, IntPtr.Zero, 0, setSpeed, valueAddress, 0, IntPtr.Zero);
            Kernel32.WaitForSingleObject(thread, uint.MaxValue);
            Free(valueAddress);
        }
```
