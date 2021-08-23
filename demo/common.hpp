#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // endof extern "C"
#endif

#include <iostream>
#include <CL/opencl.h>
#include <CL/cl.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <string>

using namespace std;
#define ARRAY_SIZE 10000

namespace OpenCL
{
  class startup
  {
    public:
	    int Check_OpenCL_Model();
	    int Check_devices_Model();
	    int Create_Context_Transfer();
	    int Create_Kernel_Method(char *filename);
	    void Cleanup();
	    bool Create_Mem_Object(float *a,float *b);
	    int Mem_Write_Kernel(char *filename);
	    int Mem_Read_Kernel();

    private:
	    cl_platform_id platform;
            cl_device_id device;
            cl_context context;
            cl_command_queue commandQueue;
            cl_program program;
            cl_kernel kernel;
            cl_mem memObjects[3];
  };
}


