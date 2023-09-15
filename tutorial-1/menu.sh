#! /bin/bash

# Program of menu driven program of maintaining employee record

#Print menu
print_menu(){
echo "Menu:"
echo "Enter 1 for creating an employee record"
echo "Enter 2 for deleting an employee record"
echo "Enter 3 for searching a record based on employee-number"
echo "Enter 4 for displaying employee records"
echo "Enter 5 for sorting all records based on employee-number"
echo "Enter 6 for listing all records"
echo "Enter any other number to exit the program"
}

add_record(){
	echo "Enter employee-name: "
	read name
	echo "Enter employee-number: "
	read num
	echo "Enter telephone number: "
	read phone
	if grep -q "^.*:$num:.*$" menu_emp_record.txt;
		then echo "Employee number $num already exists, not going to create a new employee record."
	else
		echo "$name:$num:$phone">> menu_emp_record.txt
		echo "Employee record created."
	fi
}

delete_record(){
	echo "Enter employee-number: "
	read num
	grep -v "^.*:$num:.*$" menu_emp_record.txt > temp.txt
	mv temp.txt menu_emp_record.txt
	echo "Employee=$num record deleted."
}

search_record(){
	echo "Enter employee-number to find:"
	read num
	grep "^.*:$num:.*$" menu_emp_record.txt | tr ':' ' '
}

get_sorted_records(){
	sort -t ':' -k2n menu_emp_record.txt > temp.txt
	mv temp.txt menu_emp_record.txt
	echo "Records are sorted now."
}

get_all_records(){
	sed 's/:/ /g' menu_emp_record.txt
}

while true;
do
	print_menu
	read option
	case $option in
	1)add_record;;
	2)delete_record;;
	3)search_record;;
	4)search_record;;
	5)get_sorted_records;;
	6)get_all_records;;
	*)echo "existing the program"
	exit 0
	;;
	esac
	echo ""
done
