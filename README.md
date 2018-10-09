# code_sample_win_platform
This project contains code samples of C++ and C# code on windows platform, mainly MSVS projects
* Named pipe example in C#, a server and a client, in c_sharp/named_pipe_client.
* Normal distributed random number generator in C3, using the [Box-Muller algorithm](https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform)in /c_sharp/normal_distribution/.
* A dll class written in C++, which operates on an unique device connected to the PC. A C# class which wrap the dll and marshal all call to the dll is built upon it. Assuming that the device returns RGGB Bayer format as part of data retrived from the device, the wrapper class also performs conversion to normal Bitmaps. 
