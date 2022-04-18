sudo apt-get install libyaml-cpp-dev googletest
make


My g++ version is:
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) 



So my logic here is sort the hikers into which bridge they 1st appear at. My propgram will exit with an error message if there aren't any hikers at the 0th bridge. Then at each bridge, you grab the hikers that appear at that bridge, and add to the currentHikerSet. That set is sorted by speed. So calcSpeed is very easy.... since the 1st hiker in currentHikerSet is the fastest hiker, they should carry the torch back across to collect the next person. Loop over bridges.

Everything is sitting in 1 file, which is not how you would want to do production code.... but there is nothing complicated enough going on in here to warrent splitting things up into different files. I mean... my only class is straight public.


If you are looking at this Monday, it won't have any tests. I will try to get to that Monday night. I got this assignment Friday afternoon... I'm a big believer in TDD, but I spent most of the time on this assignment figuring out how YAML worked. I recall using it once about 10 years ago. 
