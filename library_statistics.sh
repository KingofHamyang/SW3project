#!/bin/bash

mkdir -p resource
mkdir -p output






if [ "$1" == "resource" ]
then
g++ -std=c++11 main.cpp
./a.out
    
    if [ "$2" == "book" ]
    then
    rm -f ./resource/book.dat
        cat ./resource.dat | while read -a line
        do
            if [ "${line[0]}" == "Book" ]
            then
                echo ${line[1]} >> ./resource/book.dat
            fi
            
        done
    fi

    if [ "$2" == "e-book" ]
    then
        rm -f ./resource/E_book.dat
        cat ./resource.dat | while read -a line
        do
            if [ "${line[0]}" == "E-book" ]
            then
                echo ${line[1]} >> ./resource/e_book.dat
            fi
            
        done
    fi

    if [ "$2" == "magazine" ]
    then
        rm -f ./resource/Magazine.dat
        cat ./resource.dat | while read -a line
        do

            if [ "${line[0]}" == "Magazine" ]
            then
                
                echo ${line[1]} >> ./resource/magazine.dat
            fi
            
        done
    fi

    
    if [ "$2" == "all" ]
    then

        rm -f ./resource/book.dat
        rm -f ./resource/e_book.dat
        rm -f ./resource/magazine.dat

        cat ./resource.dat | while read -a line
        do
            
            if [ "${line[0]}" == "Magazine" ]
            then
                
                echo ${line[1]} >> ./resource/magazine.dat
            fi

            if [ "${line[0]}" == "E-book" ]
            then
                echo ${line[1]} >> ./resource/e_book.dat
            fi

            if [ "${line[0]}" == "Book" ]
            then
                echo ${line[1]} >> ./resource/book.dat
            fi
            
            
        done

    fi


fi

if [ "$1" == "output" ]
then
    rm -f ./output/stat_table.dat
    x=-1
    g++ -std=c++11 main.cpp
    ./a.out
    while [ $x -le 16 ]
    do
        num=0
        while read -a line
        do
            if [ "$x" == "${line[1]}" ]
            then
                ((num++))
                echo ${line[1]}$'\t'$num
                
            fi
            

        done < ./output.dat
        
        echo $x$'\t'$num >> ./output/stat_table.dat
        ((x++))
    done
fi

if [ "$1" == "space" ]
then
    if [ "$2" == "studyroom" ]
    then
        cp ./space.dat ./temp_space.dat

        num=0;

        cat ./temp_space.dat | while read -a line
        do
            echo ${line[@]}
            if [ $num == 0 ]
            then
                echo ${line[@]} > ./space.dat
            else
                echo ${line[@]} >> ./space.dat
            fi
            ((num++))
            
        done

    fi
fi
