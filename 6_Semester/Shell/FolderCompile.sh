#!/bin/bash
                                                                        # Wo ist Ihr Kommentar-Header???
#Neccessary variables
verboseMode=0
argumentPosition=0

#Version function which shows version of script and author
#######################################
Version()                                                               # Braucht man dafür wirklich eine Funktion?
{
   # Display Version
   echo "Folder-compiling script version 1.0 released on 01.08.2022"
   echo "Author: Luis Waldhauser"
   echo ""
                                                                        return 0
}
#######################################

#Help function which shows manpage when script started with -h
#######################################
Help()
{
   # Display Help
   echo "Script to compile a complete folder of C-files with gcc
         Insert the path to the folder and flags for the compiler
         Compiler flags as standard for gcc
   
         Syntax: folderCompile.sh *[-h|v|V] [datapath] *[-options for GCC]
         Example call: ./FolderCompile.sh -v '/home/user/bin' -Wall -O2

         Files with spaces in the name are not processed
   
         Logfile is created in folder of C-files
         Logfile named FolderCompileLog_'timestamp'.txt

         options:
         -h/--help         Print this Help.
         -v/--verbose      Verbose mode.
         -V/--version      Print software version, general information and exit."
   echo
                                                                        return 0
}
                                                                        # A --clean option would have been a good idea.
                                                                        
#######################################

#Process script options
while [[ "${1-}" =~ ^- ]]; do
   case "$1" in
      -h | --help) # display Help
         Help
         exit 0;;
      -v | --verbose) # Activate verbose mode, variable which activates if-clauses
         verboseMode=1;;
      -V | --version)   # display version, author
         Version
         exit 0;;
   esac
   shift
done

#Creating name for log file
timestamp=$(date +%d.%m\\%T)                                            # A backslash is a tremendously bad idea, because it is an invalid filename 
                                                                        # on a NTFS filesystem.
logfile=FolderCompileLog_$timestamp.txt

#finding datapath in arguments and saving to variable
for var in "$@"; do
   argumentPosition=$((argumentPosition+1))
	if [[ -d $var  ]]; then
		datapath=${var}
      break
	fi 
done

#Terminate if no path is given
if [[ -z "$datapath" ]]; then
	echo Please insert datapath and start script again
	echo Terminating script 
	exit 1
fi

#Changing workingdirectory to given path
cd $datapath
if [[ $? > 0 ]]; then
	echo Error with datapath 
	exit 1
fi

#Verbose comment
if [[ $verboseMode == 1 ]]; then
   echo Datapath correct                                                ": $(pwd)"
fi

#Logging
echo Folder to compile: $datapath >> $logfile
echo '' >> $logfile
echo Files with space in name will be ignored | tee -a $logfile         # Why do exclude filenames with spaces? There is no need to do so :-(
echo '' >> $logfile


#Saving flags to varaible
flags="${@: $(($argumentPosition+1)): $(($#-$argumentPosition))}"

#Saving flags in second variable with additional character 
#for easier handling later
flagsCheck=$flags" t"

#Checking if all compilerflags begin with dash, else terminate script
#Going through flag string until only additional character left
while [[ ${#flagsCheck} > 1 ]]; do
   #Deleting until first space, if first character is a dash
   if [[ ${flagsCheck::1} == "-" ]]; then
      flagsCheck=${flagsCheck#*' '}
   #Error if flag does not start with a dash
   else
      echo Flag not correct | tee -a $logfile
      echo No - before compiler flag ${flagsCheck%%' '*} | tee -a $logfile
      exit 1
   fi
done
                                                                        # This is not correct. If no flags have been specified at all,
                                                                        # your script will bail out here  :-(
                                                                        # Concerning the technique: Just loop over the parameters. Easy and simple.
                                                                        
                                                                        # Furthermore, I cannot specify any option which requires an argument, e.g.
                                                                        # a define or an include path, e.g. "-I /$HOME/C/Include"    :-(


#Creating dummy c-file to check if compiler flags are supported by GCC
#Only check for existance not if they are correct with the files
echo '#include <stdio.h>
int main() {
   printf("Hello, World!\n");
   return 0;
}' > flagTest.c

#Compiling test programm with flags and terminate programm if error occurs
#Deleting dummy programm afterwards
out=$(gcc flagTest.c -o flagTest.o $flags 2>&1)
#GCC returns 0 for correct compilation and warnings, 1 is only when error occurs
if [ $? -ne 0 ]; then
    echo Flags not correct: | tee -a $logfile
    echo $out | tee -a $logfile
    rm flagTest.c
    exit 1
 else
   rm flagTest.c
   rm flagTest.o
fi
                                                                        # This test is not really convincing. 
#Logging
echo Compiling with flags $flags >> $logfile
echo '' >> $logfile

#Verbose comment
if [[ $verboseMode == 1 ]]; then
   echo Flags correct
fi


#Compiling all files in folder, ignoring files with space in name
#Files with space no possible way found to compile                      
#Using different IFS setting sometimes changes flags variable
#Quoting filename only works in commandline, when inserting quoted name from
#variable, quotes are not expressed correct                             # This is not true and a disappointment :-(

# for filename in $(ls *.c | grep -F -v ' '); do
                                                                        IFS=$'\n'
                                                                        for filename in $(ls -1 *.c ) ; do
                                                                           echo "Filename=$filename"
   #Creating new filename
	filenameNew=${filename::-2}.o                                        # FilenameObj might be a better name for object files.
                                                                        # However, you are not going to compile an object file, 
                                                                        # but an executable, which has an "exe" suffix in Windows 
                                                                        # and no suffix at all under Unix.  :-(

   #GCC and output to variable
	output=$(gcc $filename -o $filenameNew $flags 2>&1)
                                                                        gcc "$filename" -o "$filenameNew" $flags 
                                                

   #Check of output to generate warnings
   #GCC only returns 1 for error and 0 everything else
   #No own return state for warnings
   if [ $? -ne 0 ]; then
      output=${output%%'|'*}
      echo Error with $filename: >> $logfile
      echo ${output::-2} >> $logfile
      echo $filename not compiled >> $logfile

      #Verbose comment
      if [[ $verboseMode == 1 ]]; then
         echo Error with $filename:
         echo ${output::-2} 
         echo $filename not compiled
         echo ' '
      fi
      #If return is 0, checking GCC dialog for warning
   else
      if grep "warning:" <<<"${output}" >/dev/null ; then
         output=${output%%'|'*}                                         # It is not a helpful idea to shorten the diagnostic output.
                                                                        # The better way is to retain the original formatting of the output.
         echo Warning with $filename: >> $logfile
         echo ${output::-2} >> $logfile

         #Verbose comment
         if [[ $verboseMode == 1 ]]; then
            echo Warning with $filename:
            echo ${output::-2}
            echo ' '
         fi
         #If return is 0 an no warning in GCC dialog -> copilation correct
      else
         echo $filename Compiling complete >> $logfile

         #Verbose comment
         if [[ $verboseMode == 1 ]]; then
            echo $filename Compiling complete
            echo ' '
         fi
      fi
   fi
   echo ' ' >> $logfile
done;

echo Script successfull | tee -a $logfile
exit 0

                                                                        # Your script can be considered as a nice exercise, but it is not
                                                                        # of real value for production or daily use.
                                                                        
                                                                        # We talked already about the fact that this is basically a job for a makefile.
                                                                        
                                                                        # Moreover, the core functionality can be achieved by one line of code:
                                                                        
                                                                        find . -maxdepth 1 -type f -name "*.c" -print -exec gcc -O2 {} 2>&1 \; | tee compile_$(date +%Y%m%d).log
                                                                        
                                                                        # So the program is too long for too less benefit.
                                                                        # And then there are some problems I expected you to solve:
                                                                        # - Filenames with spaces should be supported
                                                                        # - Compiler options with parameters should be possible
                                                                        # - You produce executables and no object files
                                                                        # - Diagnostic output in logfiles should not be truncated
                                                                        
                                                                        # 2.0
                                                                        
                                                                        
                                                                        
