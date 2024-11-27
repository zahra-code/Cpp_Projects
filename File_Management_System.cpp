#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>
#include <regex>
#include <string>
using namespace std;
using namespace std::filesystem;

string create_path(string drive, string directory, string file)
{
    string path;
    path = drive + ":/" + directory + "/" + file;
    return path;
}
void check_file_existence(string filename)
{
    path p1{filename};
    if (exists(filename))
    {
        cout << "file found at " << p1.parent_path() << endl;
    }
    else
    {
        cout << "No such FILE found!! with name " << '"' << filename << '"' << endl;
    }
}
void check_directory_existence(string directory)
{
    path p1{directory};
    if (exists(directory))
    {
        cout << "file found at " << p1.parent_path() << endl;
    }
    else
    {
        cout << "No such DIRECTORY found!! with name " << '"' << directory << '"' << endl;
    }
}
void file_details(string filename)
{
    path p1{filename};
    if (exists(filename))
    {
        cout << "\t FILE details:" << endl;
        cout << "Status = Exists" << endl;
        cout << "File name = " << p1.filename() << endl;
        cout << "Directory = " << p1.parent_path() << endl;
        cout << "File extension = " << p1.extension() << endl;
        try
        {
            cout << "File size (bytes) = " << file_size(p1) << endl;
        }
        catch (const filesystem_error &e)
        {
            cerr << "File size (bytes) =  -" << endl;
        }
    }
    else
    {
        cout << "No such DIRECTORY/FILE found!! with name " << '"' << filename << '"' << endl;
    }
}
void view_files_in_a_directory(string directory)
{
    path p1{directory};
    int n = 1;
    if (exists(directory))
    {
        cout << "FILES in directory = " << directory << endl;
        for (const auto &entry : directory_iterator(directory))
        {
            cout << "File " << n << ": " << entry.path() << endl;
            n++;
        }
    }
    else
    {
        cout << "No such DIRECTORY found!! with name " << '"' << directory << '"' << endl;
    }
}
int main()
{
    int choice;
    cout << "\tWelcome to command-line based FILE MANAGEMENT SYSTEM" << endl;

    while (true)
    {
        while (true)
        {
            cout << "SELECT AN OPTION: " << endl;
            cout << "1. File Functions" << endl;
            cout << "2. Directory Functions" << endl;
            cout << "3. Exit" << endl;
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ENTER a valid INPUT!!" << endl;
            }
            else if (choice < 1 || choice > 3)
            {
                cout << "ENTER a valid INPUT!!" << endl;
            }
            else
            {
                break;
            }
        }

        switch (choice)
        {
        case 1:
        { // File Functions
            int file_choice, ans;
            string drive1, directory1, file1;
            string directory, file, path_str, drive, new_name, extension;

            path p1, destination; // Declare `p1` at a higher scope

            cout << "SELECT an option: " << endl;
            cout << "1. Get File details" << endl;
            cout << "2. Rename a file" << endl;
            cout << "3. Delete a file" << endl;
            cout << "4. Create a file" << endl;
            cout << "5. Copy a file" << endl;
            cout << "6. Move a file to another directory" << endl;
            cout << "7. Change the extension of a file" << endl;
            cout << "8. View File content" << endl;
            cout << "9. Exit to main menu" << endl;
            cin >> file_choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Would you like to provide the path or directory?" << endl;
            cout << "1. Path    2. Directory" << endl;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1)
            {
                cout << "Enter path of file: ";
                getline(cin, path_str);

                // Remove quotes if present
                if (regex_search(path_str, regex(R"(["])")))
                {
                    path_str = regex_replace(path_str, regex(R"(["'])"), "");
                }

                p1 = path(path_str); // Assign value to `p1`

                drive = p1.root_name().string(); // Drive letter (e.g., "C:")
                drive = regex_replace(drive, regex(R"([:])"), "");
                directory = p1.parent_path().string(); // Directory path
                directory = regex_replace(directory, regex(R"(^[a-zA-Z]*[:/\\].)"), "");
                string filename = p1.stem().string(); // Filename without extension
                string extension = p1.extension().string();
                file = filename + extension;
            }
            else if (choice == 2)
            {
                cout << "Enter name of drive: ";
                getline(cin, drive);
                cout << "Enter name of directory: ";
                getline(cin, directory);
                cout << "Enter name of file: ";
                getline(cin, file);
                path_str = drive + ":/" + directory + "/" + file;
                p1 = path(path_str); // Assign value to `p1`
            }
            else
            {
                cout << "INVALID OPTION!" << endl;
            }

            switch (file_choice)
            {
            case 1: // File details
                if (!path_str.empty())
                {
                    file_details(path_str);
                }
                else
                {
                    cout << "No file path provided!" << endl;
                }
                break;
            case 2: // Rename a file
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                try
                {
                    cout << "Enter new name of file (just enter name of file): " << endl;
                    cin >> new_name;
                    new_name = drive + ":/" + directory + "/" + new_name;
                    rename(p1, path(new_name));
                    cout << "File renamed successfully!!" << endl;
                }
                catch (const filesystem_error &e)
                {
                    cout << "Some error occured...FILE name CAN'T be renamed...TRY AGAIN LATER";
                }

                break;
            case 3: // delete a file
                if (exists(path_str))
                {
                    cout << "You surely want to delete file '" << file << "' ?" << endl;
                    cout << "1. Yes      2. No" << endl;
                    cin >> ans;
                    if (ans == 1)
                    {
                        try
                        {
                            remove(p1);
                            cout << "FILE '" << file << "' deleted successfully!" << endl;
                        }
                        catch (const filesystem_error &e)
                        {
                            cout << "Some error occured...FILE name CAN'T be deleted...TRY AGAIN LATER" << endl;
                        }
                    }
                    else
                    {
                        cout << "Understood!! Moving to main menu." << endl;
                        break;
                    }
                }
                else
                {
                    cout << "NO such file found '" << p1 << "' !!" << endl;
                }
                break;
            case 4: // create a new file
                if (!exists(path_str))
                {
                    ofstream outfile(path_str);
                    if (!outfile)
                    {
                        cout << "Some error occured...File name CAN'T be created...TRY AGAIN LATER";
                    }
                    else
                    {
                        cout << "FILE '" << path_str << "' created successfully!!" << endl;
                    }
                    outfile.close();
                }
                else
                {
                    cout << "File already exists named '" << path_str << "' !!" << endl;
                }
                break;
            case 5: // copy a file
                if (exists(path_str))
                {
                    file1 = p1.stem().string() + "(1)" + p1.extension().string();
                    destination = current_path() / file1; // Current directory + original filename
                    cout << destination << endl;
                    try
                    {
                        copy(p1, destination, copy_options::overwrite_existing);
                        cout << "FILE '" << file << "' copied successfully! at " << drive + ":/" + directory << endl;
                    }
                    catch (const filesystem_error &e)
                    {
                        cout << "Some error occured..FILE CAN'T be copied...TRY AGAIN LATER..." << e.what() << endl;
                    }
                }
                else
                {
                    cout << "NO such file found '" << p1 << "' !!" << endl;
                }
                break;
            case 6: // move the file
                if (exists(p1))
                {
                    cout << "Enter new location of file:" << endl;
                    cout << "New drive: ";
                    getline(cin, drive1);
                    cout << "New directory: ";
                    getline(cin, directory1);
                    destination = drive1 + ":/" + directory1 + "/" + file;
                    cout << "Do you want to move it or just copy at new location? (1. Move   2. Only Copy)" << endl;
                    cin >> choice;
                    if (exists(destination))
                    {
                        string file1 = p1.stem().string() + "(1)" + p1.extension().string();
                        destination = drive1 + ":/" + directory1 + "/" + file1; // Current directory + original filename
                        cout << destination << endl;
                        try
                        {
                            copy(p1, destination, copy_options::overwrite_existing);
                            cout << "FILE '" << file1 << "' moved/copied successfully! at " << drive1 + ":/" + directory1 << endl;
                        }
                        catch (const filesystem_error &e)
                        {
                            cout << "Some error occured..FILE CAN'T be moved...TRY AGAIN LATER..." << e.what() << endl;
                        }
                    }
                    else if (!exists(destination))
                    {
                        try
                        {
                            copy(p1, destination);
                            cout << "FILE '" << file << "' moved/copied successfully! at " << drive + ":/" + directory << endl;
                        }
                        catch (const filesystem_error &e)
                        {
                            cout << "Some error occured..FILE CAN'T be copied...TRY AGAIN LATER..." << e.what() << endl;
                        }
                        if (choice == 1)
                        {
                            remove(p1);
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                else
                {
                    cout << "NO such file found '" << p1 << "' !!" << endl;
                }

                break;
            case 7: // change the extension of file
                if (exists(path_str))
                {
                    try
                    {
                        cout << "Enter the new extension for you file( .bin, .txt etc) = ";
                        cin >> extension;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        path new_path = p1;
                        new_path.replace_extension(extension);
                        // Rename the file to apply the new extension
                        rename(p1, new_path);
                        cout << "FILE '" << file << "' extension changed successfully to '" << new_path.extension().string() << "'!" << endl;
                    }
                    catch (const filesystem_error &e)
                    {
                        cout << "Some error occured...Extension of FILE CAN'T be changed...TRY AGAIN LATER" << endl;
                    }
                }
                else
                {
                    cout << "NO such file found '" << p1 << "' !!" << endl;
                }
                break;
            case 8: // view content of a file
            if(exists(p1)){
                ifstream inFile(path_str);
                if(!inFile){
                    cout<<"Some Error Occured!! Try Again LATER!!"<<endl;
                }
                else{
                    string line;
                    cout<<"\t READING the File '"<<file<<"' : "<<endl;
                    while(getline(inFile,line)){
                        cout<<line<<endl;
                    }
                }
                cout<<endl;
                inFile.close();
            }
            else{
                cout << "NO such file found '" << p1 << "' !!" << endl;
            }
                break;
            case 9:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "INVALID INPUT!" << endl;
                break;
            }
            break;
        }

        case 2:
        { // Directory Functions
            int dir_choice, choice;
            string directory, file, path_str, drive, new_name;
            path p1; // Declare `p1` at a higher scope

            cout << "SELECT an option: " << endl;
            cout << "1. View files in the Directory" << endl;
            cout << "2. Create a directory" << endl;
            cout << "3. Delete a directory" << endl;
            cout << "4. Exit to main menu" << endl;
            cin >> dir_choice;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Would you like to provide the path or directory?" << endl;
            cout << "1. Path    2. Directory" << endl;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1)
            {
                cout << "Enter path of directory: ";
                getline(cin, path_str);

                // Remove quotes if present
                if (regex_search(path_str, regex(R"(["])")))
                {
                    path_str = regex_replace(path_str, regex(R"(["'])"), "");
                }

                p1 = path(path_str); // Assign value to `p1`

                drive = p1.root_name().string(); // Drive letter (e.g., "C:")
                drive = regex_replace(drive, regex(R"([:])"), "");
                directory = p1.stem().string(); // Directory path
            }
            else if (choice == 2)
            {
                cout << "Enter name of drive: ";
                getline(cin, drive);
                cout << "Enter name of directory: ";
                getline(cin, directory);
                path_str = drive + ":/" + directory;
                p1 = path(path_str); // Assign value to `p1`
            }
            else
            {
                cout << "INVALID OPTION!" << endl;
            }
            switch (dir_choice)
            {
            case 1: // view files in a directory
                if (exists(path_str))
                {
                    view_files_in_a_directory(path_str);
                }
                else
                {
                    cout << "NO directory found '" << p1 << "' !!!" << endl;
                }
                break;
            case 2: // create a new directory
                if (!exists(path_str))
                {
                    try
                    {
                        create_directory(p1);
                        cout << "Directory '" << path_str << "' created successfully!!" << endl;
                    }
                    catch (const filesystem_error &e)
                    {
                        cout << "Some error occured...Directory name CAN'T be created...TRY AGAIN LATER";
                    }
                }
                else
                {
                    cout << "Directory already exists named '" << path_str << "' !!" << endl;
                }
                break;
            case 3: // delete a directory
                if (exists(path_str))
                {
                    try
                    {
                        remove_all(path_str);
                        cout << "DIRECTORY '" << path_str << "' deleted successfully!!!" << endl;
                    }
                    catch (const filesystem_error &e)
                    {
                        cout << "Some error occured...Directory name CAN'T be deleted...TRY AGAIN LATER";
                    }
                }
                else
                {
                    cout << "NO directory found '" << p1 << "' !!!" << endl;
                }
                break;
            case 4:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "INVALID INPUT!" << endl;
                break;
            }
            break;
        }
        case 3: // Exit
            cout << "GOOD-BYE!" << endl;
            return 0;

        default:
            cout << "INVALID INPUT!" << endl;
            break;
        }
    }
    return 0;
}
