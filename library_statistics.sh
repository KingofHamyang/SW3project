#!/bin/bash

mkdir -p resource
mkdir -p output
mkdir -p input
mkdir -p space





if [ "$1" == "resource" ]
then

    
    if [ "$2" == "book" ]
    then
    rm -f ./resource/book.dat
        awk '{print}' ./resource.dat | while read -a line
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
        awk '{print}' ./resource.dat | while read -a line
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
       awk '{print}' ./resource.dat | while read -a line
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

        awk '{print}' ./resource.dat | while read -a line
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
    cp ./input.dat ./temp_input_test.dat
    rm ./input.dat
    if [ "$2" == "studyroom" ]
    then
    echo doneds
        cp ./space.dat ./temp_space.dat
        num=0
       
        awk '{print}' ./temp_space.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./space.dat
                echo ${line[@]} > ./input.dat
            

            elif [ "StudyRoom" == "${line[1]}" ]
            then
                if [ "$3" == "${line[2]}" -o "$3" == "all" ]
                then
                    echo ${line[@]} >> ./space.dat
                fi
                
            fi

            
        done
        cp ./output.dat ./temp_out.dat
        ./a.out
        echo doneds


        rm space.dat
        cp ./temp_space.dat ./space.dat

        
        cp ./output.dat ./space/studyroom.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        

    

    elif [ "$2" == "seat" ]
    then
        cp ./space.dat ./temp_space.dat
        num=0
       
        awk '{print}' ./temp_space.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./space.dat
                echo ${line[@]} > ./input.dat
            

            elif [ "Seat" == "${line[1]}" ]
            then
                if [ "$3" == "${line[2]}" -o "$3" == "all" ]
                then
                    echo ${line[@]} >> ./space.dat
                fi
                
            fi


            
        done
        cp ./output.dat ./temp_out.dat
        ./a.out
        cp space.dat test_.dat
        rm space.dat
        cp ./temp_space.dat ./space.dat

                
        cp ./output.dat ./space/seat.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        


    elif [ "$2" == "undergraduate" ]
    then
        cp ./space.dat ./temp_space.dat
        num=0
       
        awk '{print}' ./temp_space.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./space.dat
                echo ${line[@]} > ./input.dat
            

            elif [ "Undergraduate" == "${line[4]}" ]
            then

                    echo ${line[@]} >> ./space.dat
                
            fi


            
        done
        cp ./output.dat ./temp_out.dat
        ./a.out
        cp space.dat test_.dat
        rm space.dat
        cp ./temp_space.dat ./space.dat

        cp ./output.dat ./space/undergraduate.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        

    

    elif [ "$2" == "graduate" ]
    then
        cp ./space.dat ./temp_space.dat
        num=0
       
        awk '{print}' ./temp_space.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./space.dat
                echo ${line[@]} > ./input.dat
            

            elif [ "Graduate" == "${line[4]}" ]
            then

                    echo ${line[@]} >> ./space.dat
                
            fi


            
        done


        cp ./output.dat ./temp_out.dat
        ./a.out
        cp space.dat test_.dat
        rm space.dat
        cp ./temp_space.dat ./space.dat

        cp ./output.dat ./space/graduate.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        
        

    

    elif [ "$2" == "faculty" ]
    then
        cp ./space.dat ./temp_space.dat
        num=0
       
        awk '{print}' ./temp_space.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./space.dat
                echo ${line[@]} > ./input.dat
            

            elif [ "Faculty" == "${line[4]}" ]
            then

                    echo ${line[@]} >> ./space.dat
                
            fi


            
        done


        cp ./output.dat ./temp_out.dat
        ./a.out
        cp space.dat test_.dat
        rm space.dat
        cp ./temp_space.dat ./space.dat

        cp ./output.dat ./space/faculty.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        
        
        

    

    elif [ "$2" == "all" ]
    then

        ./library_statistics.sh space studyroom all
        ./library_statistics.sh space seat all
        ./library_statistics.sh space undergraduate
        ./library_statistics.sh space graduate
        ./library_statistics.sh space faculty

        
        

    elif [ "$2" == "date" ]
    then
        cp ./space.dat ./temp_space.dat
        num=0

        year_low=`echo $3 | cut -d "/" -f1`
        year_high=`echo $4 | cut -d "/" -f1`
        month_low=`echo $3 | cut -d "/" -f2`
        month_high=`echo $4 | cut -d "/" -f2`
        date_low=`echo $3 | cut -d "/" -f3`
        date_high=`echo $4 | cut -d "/" -f3`
        hour_low=`echo $3 | cut -d "/" -f4`
        hour_high=`echo $4 | cut -d "/" -f4`
        
        time_low=`expr $year_low \* 8640 + $month_low \* 720 + $date_low \* 24 + $hour_low`
        time_high=`expr $year_high \* 8640 + $month_high \* 720 + $date_high \* 24 + $hour_high`

        echo $year_high
        echo $year_low
       
        awk '{print}' ./temp_space.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./space.dat
                echo ${line[@]} > ./input.dat
            

            else
                echo ${line[0]}
                year=`echo ${line[0]} | cut -d "/" -f1`
                month=`echo ${line[0]} | cut -d "/" -f2`
                date=`echo ${line[0]} | cut -d "/" -f3`
                hour=`echo ${line[0]} | cut -d "/" -f4`

                time=`expr $year \* 8640 + $month \* 720 + $date \* 24 + $hour`

                echo $year$'\t'$month$'\t'$date

                echo $time

                if [ $time -le $time_high -a $time -ge $time_low ] 
                then
                    echo asdf
                    echo ${line[@]} >> ./space.dat
                fi
                
            fi

            
        done
        


        cp ./output.dat ./temp_out.dat
        ./a.out
        cp space.dat test_.dat
        rm space.dat
        cp ./temp_space.dat ./space.dat

        cp ./output.dat ./space/date.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        
    fi

    if [ "$2" != "all" ]
    then

    rm ./input.dat
    cp ./temp_input_test.dat ./input.dat 
    rm ./temp_input_test.dat
    fi

fi


####### input file

if [ "$1" == "input" ]
then
    cp ./space.dat ./temp_space_test.dat
    rm ./space.dat
    if [ "$2" == "book" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0
       
        awk '{print}' ./temp_input.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
                
            

            elif [ "Book" == "${line[1]}" ]
            then

                    echo ${line[@]} >> ./input.dat

                
            fi

            
        done


        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/book.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
        
        


    elif [ "$2" == "e-book" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0
       
        awk '{print}' ./temp_input.dat | while read -a line
        do
            
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
            

            elif [ "E-book" == "${line[1]}" ]
            then

                    echo ${line[@]} >> ./input.dat

                
            fi

            
        done


        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/e-book.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat

    elif [ "$2" == "magazine" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0
        
        awk '{print}' ./temp_input.dat | while read -a line
        do
            ((num++))  

            echo ${line[0]}     
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
            
            
            elif [ "Magazine" == "${line[1]}" ]
            then
                

                    echo ${line[@]} >> ./input.dat

                
            fi

            
        done

        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/magazine.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat

    elif [ "$2" == "undergraduate" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0
       
        awk '{print}' ./temp_input.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
            

            elif [ "Undergraduate" == "${line[4]}" ]
            then

                    echo ${line[@]} >> ./input.dat

                
            fi

            
        done
       
        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/undergraduate.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat

    elif [ "$2" == "graduate" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0
       
        awk '{print}' ./temp_input.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
            

            elif [ "Graduate" == "${line[4]}" ]
            then

                    echo ${line[@]} >> ./input.dat

                
            fi

            
        done

        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/graduate.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat

    elif [ "$2" == "faculty" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0
       
        awk '{print}' ./temp_input.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
            

            elif [ "Faculty" == "${line[4]}" ]
            then

                    echo ${line[@]} >> ./input.dat

                
            fi

            
        done

        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/faculty.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
    
    elif [ "$2" == "date" ]
    then
        cp ./input.dat ./temp_input.dat
        num=0

        year_low=`echo $3 | cut -d "/" -f1`
        year_high=`echo $4 | cut -d "/" -f1`
        month_low=`echo $3 | cut -d "/" -f2`
        month_high=`echo $4 | cut -d "/" -f2`
        date_low=`echo $3 | cut -d "/" -f3`
        date_high=`echo $4 | cut -d "/" -f3`
        time_low=`expr $year_low \* 360 + $month_low \* 30 + $date_low`
        time_high=`expr $year_high \* 360 + $month_high \* 30 + $date_high`

        echo $year_high
        echo $year_low
       
        awk '{print}' ./temp_input.dat | while read -a line
        do
            ((num++))                    
            if [ $num == 1 ]
            then
                echo ${line[@]} > ./input.dat
                echo ${line[@]} > ./space.dat
            

            else
                year=`echo ${line[0]} | cut -d "/" -f1`
                month=`echo ${line[0]} | cut -d "/" -f2`
                date=`echo ${line[0]} | cut -d "/" -f3`

                time=`expr $year \* 360 + $month \* 30 + $date`

                echo $year$'\t'$month$'\t'$date

                echo $time

                if [ $time -le $time_high -a $time -ge $time_low ] 
                then
                    echo asdf
                    echo ${line[@]} >> ./input.dat
                fi
                
            fi

            
        done
        

        cp ./output.dat ./temp_out.dat
        ./a.out
        cp input.dat test_input.dat
        rm input.dat
        cp ./temp_input.dat ./input.dat

        cp ./output.dat ./input/date.dat

        rm ./output.dat

        cp temp_out.dat ./output.dat
    elif [ "$2" == "all" ]
    then

        ./library_statistics.sh input e-book
        ./library_statistics.sh input book
        ./library_statistics.sh input magazine
        ./library_statistics.sh input undergraduate
        ./library_statistics.sh input graduate
        ./library_statistics.sh input faculty



    fi

    if [ "$2" != "all" ]
    then
    rm ./space.dat
    cp ./temp_space_test.dat ./space.dat 
    rm ./temp_space_test.dat
    fi
        
        
        
        

    

  
fi
