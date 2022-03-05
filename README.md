# mchl-logger ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
A simple `library` for outputting information about the program's operation to a `file` or `console`
```C
  DEF_FILE ("docs.txt"); /*open te "docs.txt" as logfile - now all info can be placed in this file*/
```
```C
  LOG("\f\a-$TESITING! %s", "lol"); /*write log-info in file and in console*/
```
## process
###### The library implements output to both the console and the file. You can specify output to file or console. 
- log file points to the log file for the whole project
- tabs indicate the number of tabs to write before each line
- skip needed to skip line modifiers `\f`-file output `\a`-console output
![c](https://raw.githubusercontent.com/Mchl-krpch/mchl-logger/main/img/logger.jpg)
