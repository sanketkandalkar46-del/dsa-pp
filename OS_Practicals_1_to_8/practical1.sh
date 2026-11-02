#!/bin/bash

FILE="address.txt"

while true
do
    echo
    echo "===== ADDRESS BOOK ====="
    echo "1. Add Contact"
    echo "2. View Contacts"
    echo "3. Search Contact"
    echo "4. Delete Contact"
    echo "5. Exit"
    read -p "Enter your choice: " choice

    case $choice in
        1)
            read -p "Enter name: " name
            read -p "Enter phone number: " phone
            echo "$name,$phone" >> "$FILE"
            echo "Contact added successfully."
            ;;
        2)
            if [ -s "$FILE" ]; then
                echo "Name, Phone"
                cat "$FILE"
            else
                echo "Address book is empty."
            fi
            ;;
        3)
            read -p "Enter name to search: " name
            if [ -f "$FILE" ] && grep -i "^$name," "$FILE"; then
                :
            else
                echo "Contact not found."
            fi
            ;;
        4)
            read -p "Enter name to delete: " name
            if [ -f "$FILE" ]; then
                grep -iv "^$name," "$FILE" > temp.txt
                mv temp.txt "$FILE"
                echo "If the contact existed, it has been deleted."
            else
                echo "Address book is empty."
            fi
            ;;
        5)
            echo "Exiting Address Book."
            break
            ;;
        *)
            echo "Invalid choice. Try again."
            ;;
    esac
done
