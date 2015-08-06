# simply::

A small library that wants to help you write C++ when it grows up.

## building

[![Build status](https://ci.appveyor.com/api/projects/status/github/olegsych/simply?branch=master&retina=true)](https://ci.appveyor.com/project/olegsych/simply/branch/master)

Using [Visual Studio 2015](https://www.visualstudio.com/downloads):
- Open `simply.sln`
- Select _Build Solution_ from the _Build_ menu
- To switch build between `x86` and `x64` platforms, select _Configuration Manager_ from the _Build_ menu and change the _Active Solution Configuration_

Using [Developer Command Prompt for VS2015](https://msdn.microsoft.com/en-us/library/ms229859.aspx):
```
msbuild simply.sln /p:Platform=x86
msbuild simply.sln /p:Platform=x64
```

## testing

Using Visual Studio 2015:
- Select _Run_ / _All Tests_ from the _Test_ menu
- To switch test exection between `x86` and `x64` platform, select _Test Settings_ from the _Test_ menu and change the _Default Processor Architecture_.

Using Developer Command Prompt for VS2015:
```
vstest.console bin\debug\Win32\simply.assert.tests.dll /Platform:x86
vstest.console bin\debug\x64\simply.assert.tests.dll /Platform:x64
vstest.console bin\debug\Win32\simply.utility.tests.dll /Platform:x86
vstest.console bin\debug\x64\simply.utility.tests.dll /Platform:x64
```