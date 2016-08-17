# Brian
Brian is a program that proceduraly generates music and sound. It's sketches
can be found on twitter in Bot form 
[here](http://www.twitter.com/brianisnotabot).

Used in the right way, a composer can use procedurally generated music as a 
tool. Leveraging the computational power of a computer, ideas can be developed, 
unexpectedly pleasant juxtapositions can be made, and complexities can be 
managed. This is sometimes referred to as computer assisted composition. 

Brian is primarily built around the Sporth Audio Language, which borrows
many fundamental ideas from the modular synthesizer community. Using Sporth,
sounds are built up of interconnected unit generators which produce signals. 
These are known as *sketches* in Brian. Any given sketch has a general sound,
but certain aspects of the signal flow can be generated from smaller
sporth sketches. Sometimes sketches can refer to other sketches. These are
called *metasketches*.

The way to use Brian is to contribute many small ideas, which Brian will then
quilt together to make one very large idea. The theory is that eventually,
Brian will be able to help build many serious compositions based on your ideas. 

When a Sketch has been rendered, it produces JSON metadata which is stored in 
a sqlite database, which can be used to query and analyze the output of
sketches. Brian also spits out sporth code and seed data so particularly
interesting patches that end up being too short can be re-generated to
any desired length.

Brian will not write symphonies. 
Brian will not do your counterpoint homework.
Brian does not use MIDI. 
Brian does not care about pop music. 
Brian is almost formless.
