# Sparky Engine

I gave up following the tutorial as it stopped being a tutorial to become a live stream.  
Aactually, it was never a tutorial, but the first videos had more in-depth content and knowledge sharing.  
Also, for some reason not all videos are available or there are commits in between videos and it became hard to follow the series.  
This is not to diminish the work done, Cherno seems a great developer and to build a Game Engine from scratch is a great deal, but I have decided to move to other projects.

Tutorial from The Cherno https://www.youtube.com/playlist?list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_  

Followed by season two in another channel ChernoArchive https://www.youtube.com/watch?v=Zv4BN7PFGas&list=PL33Ub_ClzraN0RIx2dhQMVwc3bgAFU83_  

I updated Emscripten build instructions to compile under emsdk 3.1.19.  
- Each Freeimage module is compiled individually and all are used in the main module as I couldn't merge them into one Freeimage module.  
- Instead of `--embeded-file` I use `--preload-file` to add the assets, but for some reason audio file didn't work. Audio file had to be copied directly into `Web` folder
- Instead of `--post-js` I use `--js-library` to load Javascript module, and the code to add as library is a bit different. 
  - have to use `mergeInto(LibraryManager.library, { /*add functions here*/ })`
  - have to convert string values with `js_string = UTF8ToString(c_string)`