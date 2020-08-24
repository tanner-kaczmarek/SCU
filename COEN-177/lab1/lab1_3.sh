#Name: Tanner Kaczmarek
#Date: 3/31/20
#Title: Lab1 - step 3
#Description: This program computes the area of a circle. 


#Sample shell programs for Lab Assignment
#!/bin/sh
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
if [ $user = "tkaczmar" ]
then
       echo "Now you can proceed!"
else
       echo "Check who logged in!" 
       exit 1
fi

response="Yes"
while [ $response != "No" ]
do
        echo "Enter radius of circle: "
        read radius
        pi=3.14
        area=$(echo "$pi*$radius*$radius"|bc)
        echo "The area of the circle is $area"

        echo "Would you like to repeat for another circle [Yes/No]?"
        read response

done
