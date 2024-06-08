#include "../includes/website.hpp"

Website::Website(char *majorsFile, char *studentsFile,
                 char *coursesFile, char *professorsFile)
{
    read_files(majorsFile, studentsFile,
               coursesFile, professorsFile);
    methods.push_back(new Post());
    methods.push_back(new Put());
    methods.push_back(new Get());
    methods.push_back(new Delete());
    users.push_back(new Manager(manager_major));

    lessonId_current = 1;
    exit = false;
}

Website::~Website()
{
    for(auto u: users) delete u;
    for(auto c: courses) delete c;
    for(auto m: majors) delete m;
    for(auto l: lessons) delete l;
}

void Website::import()
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        identify_method(line);
        if(exit) break;
    }
}

void Website::identify_method(string &line)
{
    istringstream iss(line);
    string method;
    iss >> method;
    size_t i = line.find(method);

    if (i != string::npos)
    {
        line = line.substr(i + method.length());
        while (!line.empty() && line[0] == SPACE)
        {
            line = line.substr(1);
        }
    }

    try
    {
        if (method == "GET")
        {
            for (auto m : methods)
            {
                Get *g = dynamic_cast<Get *>(m);
                if (g)
                {
                    g->identify_command(line, users, currentUser, lessonId_current, lessons, courses, majors);
                }
            }
        }

        else if (method == "POST")
        {
            for (auto m : methods)
            {
                Post *post = dynamic_cast<Post *>(m);
                if (post)
                {
                    post->identify_command(line, users, currentUser, lessonId_current, lessons, courses, majors);
                }
            }
        }

        else if (method == "DELETE")
        {
            for (auto m : methods)
            {
                Delete *del = dynamic_cast<Delete *>(m);
                if (del)
                {
                    del->identify_command(line, users, currentUser, lessonId_current, lessons, courses, majors);
                }
            }
        }

        else if (method == "PUT")
        {
            for (auto m : methods)
            {
                Put *put = dynamic_cast<Put *>(m);
                if (put)
                {
                    put->identify_command(line, users, currentUser, lessonId_current, lessons, courses, majors);
                }
            }
        }

        else if (method == "QUIT"){
            exit = true;
        }

        else
        {
            throw BadRequest();
        }
    }

    catch (BadRequest &br)
    {
        cerr << br.what() << endl;
    }

    catch (Absence &a)
    {
        cerr << a.what() << endl;
    }

    catch (EmptyException &ee)
    {
        cerr << ee.what() << endl;
    }

    catch (Inaccessibility &ie)
    {
        cerr << ie.what() << endl;
    }
}

void Website::read_majors(char *majorsFileName)
{
    ifstream majorsFile(majorsFileName);
    if (!majorsFile.is_open())
        cerr << "Error: Unable to open majorsFile!" << endl;
    MD major;
    string line;
    getline(majorsFile, line);
    while (getline(majorsFile, line))
    {
        istringstream iss(line);
        string token;

        getline(iss, token, COMMA);
        major.MID = token;

        getline(iss, token, COMMA);
        major.name = token;

        majors.push_back(new Major(major));
    }
}

void Website::read_students(char *studentsFileName)
{
    ifstream studentsFile(studentsFileName);
    if (!studentsFile.is_open())
        cerr << "Error: Unable to open studentsFile!" << endl;
    SD student;
    string line;
    getline(studentsFile, line);
    while (getline(studentsFile, line))
    {
        istringstream iss(line);
        string token;

        getline(iss, token, COMMA);
        student.SID = token;

        getline(iss, token, COMMA);
        student.name = token;

        getline(iss, token, COMMA);
        student.majorID = token;
        MD studentMajor = find_MajorData_by_id(student.majorID);

        getline(iss, token, COMMA);
        student.semester = token;

        getline(iss, token, COMMA);
        student.password = token;

        users.push_back(new Student(student, studentMajor));
    }
}

void Website::read_courses(char *coursesFileName)
{
    ifstream coursesFile(coursesFileName);
    if (!coursesFile.is_open())
        cerr << "Error: Unable to open coursesFile!" << endl;
    CD course;
    string line;
    getline(coursesFile, line);
    while (getline(coursesFile, line))
    {
        istringstream iss(line);
        string token;

        getline(iss, token, COMMA);
        course.CID = token;

        getline(iss, token, COMMA);
        course.name = token;

        getline(iss, token, COMMA);
        course.credit = token;

        getline(iss, token, COMMA);
        course.prereq = token;

        getline(iss, token, COMMA);
        course.majors_id = split(token, SEMI_COLON);

        courses.push_back(new Course(course));
    }
}

void Website::read_professors(char *professorsFileName)
{
    ifstream professorsFile(professorsFileName);
    if (!professorsFile.is_open())
        cerr << "Error: Unable to open professorsFile!" << endl;
    PD prof;
    string line;
    getline(professorsFile, line);
    while (getline(professorsFile, line))
    {
        istringstream iss(line);
        string token;

        getline(iss, token, COMMA);
        prof.PID = token;

        getline(iss, token, COMMA);
        prof.name = token;

        getline(iss, token, COMMA);
        prof.majorID = token;
        MD profMajor = find_MajorData_by_id(prof.majorID);

        getline(iss, token, COMMA);
        prof.position = token;

        getline(iss, token, COMMA);
        prof.password = token;

        users.push_back(new Professor(prof, profMajor));
    }
}

vector<string> Website::split(const string &str, const char delim)
{
    vector<string> strings;
    string::size_type pos = 0;
    string::size_type prev = 0;

    while ((pos = str.find(delim, prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + sizeof(char);
    }
    strings.push_back(str.substr(prev));
    return strings;
}

void Website::read_files(char *majorsFile, char *studentsFile,
                         char *coursesFile, char *professorsFile)
{
    read_majors(majorsFile);
    read_students(studentsFile);
    read_courses(coursesFile);
    read_professors(professorsFile);
}

MD Website::find_MajorData_by_id(string userMajorId)
{
    MD major;
    for (Major *m : majors)
    {
        if (m->get_MID() == userMajorId)
        {
            major.MID = m->get_MID();
            major.name = m->get_name();
        }
    }
    return major;
}