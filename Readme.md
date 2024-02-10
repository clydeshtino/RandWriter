# RandWriter 
# By: Clyde Shtino 

## About
The purpose of this project is to take a .txt file, in this case, the story of Tom Sawyer, and it'll generate something new based on the length and k value we argue to it in the command line. k is the order of the txt file based on an integer number that we give to it. This code implements a Markov chain-based random text generation algorithm, utilizing several data structures and algorithms. The code employs data structures like maps and vectors, along with algorithms for string manipulation, randomization, and Markov chain-based text generation to implement a randomized text generator based on a given input text.

## Constructor "RandWriter::RandWriter(string text, int k)"
The constructor starts off by intializing the object with a text string and an integer "k", which represents the order of the Markov model. It'll then generate a set of unique characters ("Alpha") present in the input text. Finally, it will call build_Kgram() to build our kgram model.

## Function: build_Kgram
The build_Kgram function starts off by building a kgram model from the input text. It'll then iterate through the input text to generate kgrams (sequences of length "k") and it'll count the occurences of the subsequent characters after each kgram. As a result, it stores the kgrams and their frequences into a "kgram" map. 

## Function: freq 
The freq function performs the task of returning the frequency of the occurence of a specific kgram. 

## Function: kRand
kRands goal is to generate a random character following the given kgram, based on the frequencies of subsequent characters. It also utilizes a random shuffle to select charcters randomly based on their frequencies. 

## Function: generate
The generate function generates a string of length "L" using the Markov model. It starts off with the intial kgram and repeatedly calls our kRand function to generate subsequent characters based on the Markov model. 

## Operator Overloading
In terms of operator overloading, the stream insertion operator is overloaded to print the contents of the "alpha" set and the kgram map which will display the characters and their frequencies as a result.

