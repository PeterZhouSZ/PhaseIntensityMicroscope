#ifndef IO_HELPER_FUNCTIONS_H
#define IO_HELPER_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

// use fopen under Linux
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif

///////////////////////////////////////////////////////////////////////////////
/// \brief save optical flow in format described on vision.middlebury.edu/flow
/// \param[in] name output file name
/// \param[in] w    optical flow field width
/// \param[in] h    optical flow field height
/// \param[in] u    horizontal displacement
/// \param[in] v    vertical displacement
///////////////////////////////////////////////////////////////////////////////
void WriteFloFile(const char *name, int w, int h, const float *u, const float *v)
{
    FILE *stream;

	if ((fopen_s(&stream, name, "wb")) != 0)
	{
		printf("Could not save flow to \"%s\"\n", name);
		return;
	}

    float data = 202021.25f;
    fwrite(&data, sizeof(float), 1, stream);
    fwrite(&w, sizeof(w), 1, stream);
    fwrite(&h, sizeof(h), 1, stream);

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            const int pos = j + i * w;
            fwrite(u + pos, sizeof(float), 1, stream);
            fwrite(v + pos, sizeof(float), 1, stream);
        }
    }

    fclose(stream);
}


std::string readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


template <typename T>
void readtxt(const char *dataPath, T *data, int N)
{
	FILE *file = fopen(dataPath,"r");
    for(int i = 0; i < N; i++)
		fscanf(file, "%f\n", &data[i]); 

	// fflush(file);
    fclose(file);

	printf("%s data loaded\n", dataPath);
}	

template <typename T>
void savetxt(const char *dataPath, T *data, int N)
{
	std::ofstream file(dataPath);
  	if (file.is_open()){
		for (int i = 0; i < N; i++)
			file << std::setprecision(std::numeric_limits<T>::digits10 + 1) << data[i] << "\n";
    	file.close();
	}
	printf("%s data saved\n", dataPath);
}	


#endif

