# simply::

A small library that wants to help you write C++ when it grows up.

## building

[![Build status](https://ci.appveyor.com/api/projects/status/github/olegsych/simply?branch=master&retina=true)](https://ci.appveyor.com/project/olegsych/simply/branch/master)

Pre-requisites (can be downloaded from https://www.visualstudio.com/downloads)
- Visual Studio 2015 Community or paid

```
msbuild simply.sln /p:Platform=x86
msbuild simply.sln /p:Platform=x64
```

## testing

```
vstest.console bin\debug\Win32\simply-tests.dll /Platform:x86
vstest.console bin\debug\x64\simply-tests.dll /Platform:x64
```