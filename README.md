# Polyominoer: A Polyomino Solver
Copyright (c) 2014 Bart Massey

This is a simple polyomino solver in C using depth-first
search. I thought it would be nice for playing
*[The Talos Principle](http://www.croteam.com/talosprinciple/)*
and existing solutions seemed fiddly and complicated.

The program should compile pretty easily on most anything.

## Usage

`Polyominoer` takes two arguments:

* First is a rectangular board dimension to be filled, in
  the format *rows*`x`*columns*, e.g. `4x2`. The max board
  size is currently pretty limited. While this would be easy
  to change, the search is also currently pretty
  inefficient; some efficiency improvements would be easy
  also.

  Of course, the board size in the current implementation
  should be the number of tiles times four, or it is
  impossible to tile.

* Next is a tile string. Each character in the tile string
  represents a polyomino to be tiled. The tile name
  characters are as follows:

             I) ####

                 ##
             5) ##

                ##
             2)  ##

             T) ###
                 #

                  #
             L) ###

             P) ###
                  #

             O) ##
                ##

  The names were chosen to be as mnemonic as possible. Note
  that the board is untileable unless the number of `T`
  tiles is even (because of a parity consideration): this
  is checked up front.


An example usage is:

            polyominoer 4x7 LP22TTI

which currently produces for me the output:

            bbcceee
            bddccea
            bfddaaa
            fffgggg

A larger example:

            polyominoer 6x8 OOI22TTLLPPP

with current output:

            aabbcccc
            aabbddde
            fffkhdee
            flkkhhhe
            llkgijjj
            lgggiiij

The output has each piece given a letter, in the order that
they were specified in the tile string.

## Notes

The code is not currently commented, which is kind of
sad and reasonably easy to fix.

The program is currently limited to tetrominoes, since
[Tetris](http://tetris.com) pieces are all I currently need,
which is also kind of sad and reasonably easy to fix.

The current search has minimal pruning. *It is currently
highly sensitive to the ordering of the tile string.*
Running the example above as

            polyominoer 6x8 TTLLPPP22IOO

currently requires 1.5 minutes on my machine. This should
be fixed, probably by completely restructuring the search,
but I'm lazy. A good general rule is to specify pieces from
most to least rotational asymmetries. The number of asymmetries for the
various pieces (perhaps obviously) is:

            1) O
            2) I52
            4) TLP

This program is licensed under the "MIT License".  Please
see the file COPYING in the source distribution of this
software for license terms.
