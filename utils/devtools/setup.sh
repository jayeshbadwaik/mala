#!/bin/bash

find . -type d -name ".git" -prune -o -type d -name *mala*  -print | sed -e "p;s/mala/$1/" | xargs -n2 mv
find . -type d -name ".git" -prune -o -type f -name *mala*  -print | sed -e "p;s/mala/$1/" | xargs -n2 mv
find . -type d -name ".git" -prune -o -type f -exec sed -i "s/mala/$1/g" {} \;
find . -type d -name ".git" -prune -o -type f -exec sed -i "s/MALA/$2/g" {} \;




