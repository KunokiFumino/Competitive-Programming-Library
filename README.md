# Competitive-Programming-Library
In case if someone run into this.
The templates are kept in /modules.
Under /modules there is a cpcm.exe, it is generated from the cpcm.sln outside.
Since the total length of the templates are very long and will surely exceed the limit of length that can be post on most online judges, and it is tiring to find the templates that you need from thousands of lines of codes, so I wrote the cpcm.exe to help managing the templates. It first load the config file - /modules/config.txt, and generate a treeview from them. Then you can choose the templates from the treeview that you need, and it can copy them to clipboard, along with the templates that is called by the chosen templates.
The format of config.txt:
1st line a integer n, means that you have n templates.
Then n parts follow, the format of each part is:
1st line write anything, or leave it empty, but must exist. It is for your convenience, in case you need to modify them.
2nd line a integer f, means the its father node is part number f.
3rd line the name of this template.
4th line the path that this template is kept.
5th line a integer m, means this template has m dependences.
Then m lines follow, each line contains the name of one of the dependences.
