# bridges-cxx
This is the BRIDGES C++ Version

Authors: Kalpathi Subramanian, June 2015, Feb. 2017

Revisions:

July, 2019: Doxygen docs revamped.

April, 2019: Iterators implemented for Graph, SLelement classes

Nov 16, 2015: Kalpathi Subramanian
	Issues brought up by Dakota Carmer
	A number of fixes/bugs/inconsistencies.
August, 2016. Revisions to C++ version better alignment with Java version, 
 	Dakota Carmer, Kalpathi Subramanian
	
Feb. 2017: New datasets integrated into BRIDGES API, Gutenberg Book
Collection(meta-data only), Games dataset, Shakespeare data 
(Sonnets, Poems, Plays), IMDB Actor/Movie Curated dataset.

April 2018: More updates, bug fixes 


Notes: 

1. All Bridges classes implemented using templates, consistent with the Java version.
2. Extensive error checking, using Try/Catch exception mechanism
3. Uses C++11 features, so must use the right compiler flags to turn on C++11 features
4. Uses libCurl to connect to the server 
5. Uses rapidjson to parse JSON of external datasets


## For BRIDGES developper

### How to make a release ?

First tag the commit that you want with the correct version number. Assuming you are on that commit:

```$ git tag -a 3.0.1```

Remeber that new tags dont get pushed automatically. So you need to push them manually:

```$ git push master 3.0.1```

Then you are ready to make the package.

For the windows package go to ``packaging/windows`` and run ``make_package.sh``. You can run that from any OS that support standard bash commands.

For a linux package go to ``packaging/unix`` and run ``compile_and_prepare.sh``. You need to be on a linux environment to do that.

For a Mac package go to ``packaging/unix`` and run ``compile_and_prepare.sh``. You need to be on a mac environment to do that.
