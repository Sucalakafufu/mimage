#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <ctime>
#include <conio.h>
#include <vector>
#include <direct.h>
#include <stdio.h>
using namespace std;

char checkParam(int, char *);
void storeParam(int, char, char*[]);
bool nextIsParamOrBlank(int, char *[]);
bool checkNext(string, string);
void help();
void showVersion();
void badSyntax();
string currentDir();

const static string VERSIONNUM = "1.4";

//global vars
int length;
string date, timeV, imgPath, command = "\"C:\\Program Files\\Macrium\\Reflect\\reflect.exe\" -e Mimage.xml", 
	diskNumber = "1", partitionNumber = "1", autoVerify = "N", backupMethod = "0", compression = "1", iSector = "Y";
vector<string> params;
bool inParam = false;
char cDate[9], cTime[9];
time_t rawtime;
//struct tm *timeinfo;
struct tm timeinfo;

ofstream fout;

void main(int argc, char *argv[])
{
	length = argc;

	//get date
	_strdate_s(cDate);
	date=cDate;

	//format date
	for (unsigned int count=0;count<date.size();count++)
	{
		if (*(date.begin()+count)=='/')
			*(date.begin()+count)='_';
	}

	//get time
	time(&rawtime);
	//timeinfo = localtime(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	//strftime(cTime,9,"%I-%M%p",timeinfo);
	strftime(cTime,9,"%I-%M%p",&timeinfo);
	timeV=cTime;

	imgPath = currentDir()+"\\"+date+"@"+timeV+"\\";

	if (argc == 1)
	{
		help();
	}
	else
	{
		for (int count=1;count<argc;count++)
		{
			if (argv[count][0] == '/')
			{
				storeParam(count, checkParam(count, argv[count]), argv);
				count++;
			}
			else
				badSyntax();
		}
	}	

	fout.open("Mimage.xml");

	fout 
		<< "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
		<< "<!--                                                                                                           -->\n"
		<< "<!-- BDF v2.0.0 Image and backup definition file for Macrium Reflect v5.0                                      -->\n"
		<< "<!--                                                                                                           -->\n"
		<< "<!-- This file is a template XML to enable a Reflect backup or Image to be initiated from VB Script or an      -->\n"
		<< "<!-- MSDOS batch file.                                                                                         -->\n"
		<< "<!-- Simply modify this file if required and pass the file name as a parameter to reflect.exe.                 -->\n"
		<< "<backup_definition version =\"2.0\">\n"
		<< "<!-- backup or image file properties -->\n"
		<< "<properties>\n"
			<< "<!-- Name that appears in the log when this definition is executed -->\n"
			<< "<name>Mimage Backup</name>\n"
			<< "<!-- Auto Verify Image or Backup File.  Y - Yes, N - No  -->\n"
			<< "<autoverify>"+autoVerify+"</autoverify>\n"
			<< "<!-- 0 - Disk Image, 1 - File and folder backup -->\n"
			<< "<backup_type>0</backup_type>\n"
			<< "<!-- 0 - Full, 1 - Incremental, 2 - Differential, 3 - Auto -->\n"
			<< "<method>"+backupMethod+"</method>\n"
			<< "<!-- Compression level. 0 - No compression, 1 - Medium, 2 - High -->\n"
			<< "<!-- Applies to full file and folder backups and images only -->\n"
			<< "<compression>"+compression+"</compression>\n"
			<< "<!-- Intelligent sector copy  Y - Yes, N - No -->\n"
			<< "<!-- Applies to full disk images only -->\n"
			<< "<intelligent>"+iSector+"</intelligent>\n"
			<< "<!-- Maximum file size of the destination file -->\n"
			<< "<!-- 0 - Auto, otherwise file size in MB (1024 = 1GB) -->\n"
			<< "<!-- Applies to full file and folder backups and images only -->\n"
			<< "<maxfilesize>0</maxfilesize>\n"
			<< "<!-- Password protection. Empty - No Password, Otherwise enter password value -->\n"
			<< "<!-- Applies to full file and folder backups and images only -->\n"
			<< "<password Type=\"Clear\"></password>\n"
			<< "<!-- AES Encryption. 0 - None, 1 - Standard 128 Bit, 2 - Medium 192 Bit, 3 High 256 bit -->\n"
			<< "<!-- Applies to full file and folder backups and images only -->\n"
			<< "<aes>0</aes>\n"
			<< "<!-- Override the application defined timeout for batch jobs.  Y - Yes, N - No -->\n"
			<< "<!-- Applies to all images and backups -->\n"
			<< "<disable_timeout>N</disable_timeout>\n"
			<< "<!-- comment for the backup -->\n"
			<< "<comment></comment>\n"
			<< "<!-- Power Saving settings -->\n"
			<< "<power level=\"0\" force=\"N\">N</power>\n"
			<< "<!-- settings for email generation on backups -->\n"
			<< "<email>\n"
			<< "<!-- settings for successful backups -->\n"
			<< "<success>\n"
			<< "<!-- enable notifications for successful backup, Y = Yes, N = No -->\n"
			<< "<enabled>N</enabled>\n"
			<< "<!--  attach log file, Y = Yes, N = No -->\n"
			<< "<attach_log>N</attach_log>\n"
			<< "<!--  attach VSS log file, Y = Yes, N = No -->\n"
			<< "<attach_vss_log>N</attach_vss_log>\n"
			<< "<!-- recipients list, separate each recipient with a semi-colon (;) -->\n"
			<< "<recipients></recipients>\n"
			<< "<!-- subject, plain text only -->\n"
			<< "<subject></subject>\n"
			<< "<!-- body, plain text only, use \n for a newline -->\n"
			<< "<body></body>\n"
			<< "</success>\n"
			<< "<!-- settings for failed backups -->\n"
			<< "<failure>\n"
			<< "<!-- enable notifications for failed backup, Y = Yes, N = No -->\n"
			<< "<enabled>N</enabled>\n"
			<< "<!--  attach log file, Y = Yes, N = No -->\n"
			<< "<attach_log>N</attach_log>\n"
			<< "<!--  attach VSS log file, Y = Yes, N = No -->\n"
			<< "<attach_vss_log>N</attach_vss_log>\n"
			<< "<!-- recipients list, separate each recipient with a semi-colon (;) -->\n"
			<< "<recipients></recipients>\n"
			<< "<!-- subject, plain text only -->\n"
			<< "<subject></subject>\n"
			<< "<!-- body, plain text only, use \n for a newline -->\n"
			<< "<body></body>\n"
			<< "</failure>\n"
			<< "</email>\n"
			<< "</properties>\n"
		<< "<!-- The source of the backup  -->\n"
		<< "<source>\n"
			<< "<!-- The following applies to Disk Images only -->\n"
			<< "<image_entry id=\"1\">\n"
				<< "<!-- disk is the 1 based index of the disk to be imaged -->\n"
				<< "<!-- id is the disk signature and is used in place of the disk index if specified -->\n"
				<< " <disk>"+diskNumber+"</disk>\n"
				<< "<!-- partition is the 1 based index of the partition on the disk -->\n"
				<< "<partition>"+partitionNumber+"</partition>\n"
				<< "</image_entry>\n"
				<< "<!-- Fie and folder backup. backup ntfs permissions. Y = Yes, N = No -->\n"
				<< "<backup_ntfs_permissions />\n"
				<< "<!-- Fie and folder backup filters. Increment the 'id' for each filter-->\n"
			<< "<!-- Applies to full file and folder backups only -->\n"
			<< "<folder_entry id=\"1\">\n"
				<< "<folder></folder>\n"
				<< "</folder_entry>\n"
			<< "<!-- File filter pattern to include, separated with semi colons -->\n"
			<< "<!-- Applies to file and folder backups only -->\n"
			<< "<folder_filter id=\"1\">\n"
			<< "<!-- Folder to backup e.g. 'c:\\my documents\\'. -->\n"
			<< "<folder />\n"
			<< "<!-- Include sub-folders Y or N -->\n"
			<< "<sub_folders />\n"
			<< "<!-- File filter patterns, separated with semi colons -->\n"
			<< "<include_file_filter />\n"
			<< "<exclude_file_filter />\n"
			<< "<!-- Sub-folder filter patterns, separated with semi colons -->\n"
			<< "<include_folder_filter />\n"
			<< "<exclude_folder_filter />\n"
			<< "<!-- Exclude System files Y or N -->\n"
			<< "<exclude_system_files />\n"
			<< "<!-- Exclude Hidden files Y or N -->\n"
			<< "<exclude_hidden_files />\n"
			<< "</folder_filter>\n"
			<< "<image_entry id=\"2\">\n"
			<< "<disk id=\"DF196081\">1</disk>\n"
			<< "<partition>2</partition>\n"
			<< "</image_entry>\n"
			<< "<image_entry id=\"3\">\n"
			<< "<disk id=\"DF196081\">1</disk>\n"
			<< "<partition>3</partition>\n"
			<< "</image_entry>\n"
			<< "<image_entry id=\"4\">\n"
			<< "<disk id=\"DF196081\">1</disk>\n"
			<< "<partition>4</partition>\n"
			<< "</image_entry>\n"
			<< "</source>\n"
			<< "<!-- Destination of backup or image file  -->\n"
			<< "<destination>\n"
			<< "<!-- Fully qualified path to destination directory  -->\n"
			<< "<directory>"<<imgPath<<"</directory>\n"
			<< "<!-- Destination file name.    -->\n"
			<< "<!-- A empty name indicates that the 16 character hex name of the     -->\n"
			<< "<!-- backup set will be used. This is the recommended setting         -->\n"
			<< "<!-- Applies to full file and folder backups and Images -->\n"
			<< "<file_name></file_name>\n"
			<< "<!-- Disk Space Management -->\n"
			<< "<dsm>\n"
			<< "<!-- Active Y - Yes, N - No -->\n"
			<< "<!-- dsm_type  0 = based on age of backups -->\n"
			<< "<!--           1 = number of full backups to retain -->\n"
			<< "<active dsm_type=\"0\">N</active>\n"
			<< "<!-- Run after the backup -->\n"
			<< "<run_after>N</run_after>\n"
			<< "<!-- for dsm_type = 0 - Type 0 - Days, 1 - Weeks  -->\n"
			<< "<type>0</type>\n"
			<< "<!-- dsm_type  0 - Number of days or weeks         -->\n"
			<< "<!-- dsm_type  1 - Number of full backups to retain -->\n"
			<< "<number>30</number>\n"
			<< "</dsm>\n"
			<< "</destination>\n"
			<< "</backup_definition>\n";
		fout.close(); fout.clear();
		system(command.c_str());
		system("DEL Mimage.xml");
}

char checkParam(int pos, char *param)
{
	string arg = param;
	
	if (arg.size() != 2)
		return 'q';
	else
		return param[1];
}

void storeParam(int pos, char option, char *argv[])
{
	switch(option)
	{
	case 'h':
		if (length > 2)
			badSyntax();
		else
			help();
		break;
	case 'a':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else if (checkNext(argv[pos+1], "yes") || checkNext(argv[pos+1], "y"))
			autoVerify = "Y";
		else if (checkNext(argv[pos+1], "no") || checkNext(argv[pos+1], "n"))
			autoVerify = "N";
		else
			badSyntax();
		break;
	case 'c':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else
			compression = argv[pos+1];
		break;
	case 'd':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else
		{
			imgPath = argv[pos+1];
			imgPath=imgPath+"\\"+date+"@"+timeV+"\\"; 
		}
		break;
	case 'i':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else if (checkNext(argv[pos+1], "yes") || checkNext(argv[pos+1], "y"))
			iSector = "Y";
		else if (checkNext(argv[pos+1], "no") || checkNext(argv[pos+1], "n"))
			iSector = "N";
		else
			badSyntax();
		break;
	case 'm':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else
			backupMethod = argv[pos+1];
		break;
	case 'M':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else
		{
			command = argv[pos+1];
			command="\""+command+"\""+" -e Mimage.xml";
		}
		break;
	case 'n':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else
			diskNumber = argv[pos+1];
		break;
	case 'p':
		if (nextIsParamOrBlank(pos, argv))
			break;
		else
			partitionNumber = argv[pos+1];
		break;
	case 'v':
		if (length > 2)
			badSyntax();
		else
			showVersion();
		break;
	default:
		badSyntax();
	}
}

bool nextIsParamOrBlank(int pos, char *argv[])
{
	if (pos+1 >= length)
		return true;
	else if (argv[pos+1][0] == '/')
		return true;
	else
		return false;
}

bool checkNext(string original, string compare)
{
	string orig = original, comp = compare;
	for (unsigned int count = 0; count < orig.size(); count++)
	{
		if (isalpha(orig[count]))
			orig[count] = tolower(orig[count]);		
	}

	for (unsigned int count = 0; count < comp.size(); count++)
	{
		if (isalpha(comp[count]))
			comp[count] = tolower(comp[count]);
	}
	
	if (orig == comp)
		return true;
	else 
		return false;
}

string currentDir() 
{
	char cCurrentPath[FILENAME_MAX];
	_getcwd(cCurrentPath, sizeof(cCurrentPath));
	return cCurrentPath;
}

void badSyntax()
{
	cout << "\nIncorrect Syntax\n"
		<< "Please try mimage /h\n";
	exit(1);
}

void showVersion()
{
	cout << "Mimage Version " + VERSIONNUM + "\n";
	exit(0);
}

void help()
{
	cout << "Usage: mimage [options]\n\n"
		<< "Options\n"
		<< "\t/h\tBrings up this help dialog\n\n"
		<< "\t/a\tAutoverify (Y or N defaults to N)\n\n"
		<< "\t/c\tCompression Level (0 - No Compression, 1 - Medium, 2 - High, \n\t\tdefaults to 1)\n\n"
		<< "\t/d\tDirectory to store image file (defaults to current directory)\n\n"
		<< "\t/i\tIntelligent Sector Copy (Y or N defaults to Y)\n\n"
		<< "\t/m\tMethod of backup \n\t\t(0 - Full, 1 - Incremental, 2 - Differential, 3 - Auto, \n\t\tdefaults to 0)\n\n"
		<< "\t/M\tMacrium Reflect install directory \n\t\t(defaults to C:\\Program Files\\Macrium\\Reflect\\)\n\n"
		<< "\t/n\tDisk ID to be imaged (defaults to 1)\n\n"
		<< "\t/p\tPartition number to be imaged (defaults to 1)\n\n"
		<< "\t/v\tDisplays Mimage Version Number\n"
		;
	exit(0);
}