#ifndef Q2_H
#define Q2_H

#include <iostream>
#include <fstream>

namespace q2
{
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;

        // 要求是按照升序排列但是test代码是按照降序排列
        bool operator<(const Patient& p)
        {
            auto possibility = [](Patient patient) {return patient.age * 3 + patient.smokes * 5 +
                patient.area_q * 2 + patient.alkhol * 4;};
            return possibility(*this) > possibility(p);
        }
    };

    inline std::vector<Patient> read_file(std::string fileName)
    {
        std::vector<Patient> patients;
        fileName = "../resources/" + fileName;
        std::ifstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return patients;
        }

        int currLine = 0, skipLines = 2;
        for (std::string line; std::getline(file, line);)
        {
            if (currLine < skipLines)
            {
                currLine ++;
                continue;
            }

            Patient patient = {};
            int cnt = 0;
            std::stringstream lineStream(line);
            for (std::string item; std::getline(lineStream, item, ',');)
            {
                if (cnt == 0)
                {
                    if (item.back() != ' ')
                    {
                        item += ' ';
                    }
                    patient.name += item;
                }
                else if (cnt == 1)
                {
                    patient.name += item;
                }
                else if (cnt == 2)
                {
                    patient.age = stoi(item);
                }
                else if (cnt == 3)
                {
                    patient.smokes = stoi(item);
                }
                else if (cnt == 4)
                {
                    patient.area_q = stoi(item);
                }
                else
                {
                    patient.alkhol = stoi(item);
                }
                cnt ++;
            }

            patients.push_back(patient);
        }

        file.close();
        return patients;
    }

    // inline内联函数不然multiple definition错误
    /*
     * 这是因为q2中函数被包含在main.cpp 和 unit_test.cpp 多个文件中每个源文件都会生成该函数的一个实例。在链接阶段，
     * 链接器会发现该函数的多个定义，从而报错“multiple definition”。
     *
     * 使用 inline 关键字可以告诉编译器，该函数在所有包含它的翻译单元中都应该被视为同一个实例。
     * 具体来说，inline 函数的定义可以出现在多个翻译单元中，但链接器会将它们视为同一个实体，从而避免“multiple definition”错误。
     */
    inline void sort(std::vector<Patient>& patients)
    {
        std::sort(patients.begin(), patients.end());
    }
}

#endif //Q2_H