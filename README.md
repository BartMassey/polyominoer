# Polyominoer: A Polyomino Solver
Copyright (c) 2014 Bart Massey

This is a simple depth-first search polyomino solver in
C. I thought it would be nice for playing
*[The Talos Principle]()* and existing solutions seemed
fiddly and complicated.

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

## Notes

The code is not currently commented, which is kind of
sad. The program is currently limited to four-ominoes, since
it is all I currently need, which is also kind of sad. Both
would be reasonably easy to fix.

This program is licensed under the "MIT License".  Please
see the file COPYING in the source distribution of this
software for license terms.
