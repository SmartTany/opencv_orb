#include "common.hpp"


namespace OpenCL
{
   int startup::Check_OpenCL_Model()
   {
     cl_uint numPlatforms = 0;
     size_t stringLength =0;
     cl_int err = CL_SUCCESS;

     err = clGetPlatformIDs(0, NULL, &numPlatforms);
     if(CL_SUCCESS != err)
     {
         cout<<"Error:query numPlatforms error"<<endl;
         return 1;
     }

     vector<cl_platform_id> platforms(numPlatforms);
     err = clGetPlatformIDs(numPlatforms, &platforms[0], NULL);
     if(CL_SUCCESS != err)
     {
         cout<<"Error:memory numPlatforms error"<<endl;
         return 1;
     }
 
     printf("get devices numPlatforms: %d\n",numPlatforms);
     platform = platforms[0];
     err = clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, NULL, &stringLength);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:query infoPlatforms error"<<endl;
         return 1;
     }
  
     vector<char> platformName(stringLength);
     err = clGetPlatformInfo(platform, CL_PLATFORM_NAME, stringLength, &platformName[0], NULL);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:memory infoPlatforms error"<<endl;
         return 1;
     }
  
     printf("Selected platform: %s\n",&platformName[0]);
  
     err = clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, NULL, &stringLength);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:query VENDOR error"<<endl;
         return 1;
     }
  
     vector<char> vendorName(stringLength);
     err = clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, stringLength, &vendorName[0], NULL);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:memory VENDOR error"<<endl;
         return 1;
     }
  
     printf("Vendor           : %s\n",&vendorName[0]);
  
     err = clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, 0, NULL, &stringLength);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:query Profile error"<<endl;
         return 1;
     }
  
     vector<char> profile(stringLength);
     err = clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, stringLength, &profile[0], NULL);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:memory Profile error"<<endl;
         return 1;
     }  
  
     printf("Profile          : %s\n",&profile[0]);
   
     err = clGetPlatformInfo(platform, CL_PLATFORM_VERSION, 0, NULL, &stringLength);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:query version error"<<endl;
         return 1;
     }    
  
     vector<char> version(stringLength);
     err = clGetPlatformInfo(platform, CL_PLATFORM_VERSION, stringLength, &version[0], NULL);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:memory version error"<<endl;
         return 1;
     }
  
     printf("OpenCL Version   : %s\n",&version[0]);
  
     err = clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, 0, NULL, &stringLength);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:query extensions error"<<endl;
         return 1;
     } 
  
     vector<char> extensions(stringLength); 
     err = clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, stringLength, &extensions[0], NULL);
     if (CL_SUCCESS != err)
     {
         cout<<"Error:memory extensions error"<<endl;
         return 1;
     }
  
     cout<<"OpenCL Finish"<<endl; 
     return 0;
   }
   
   int startup::Check_devices_Model()
   {
       cl_device_type deviceType = CL_DEVICE_TYPE_GPU;
       cl_uint numDevices = 0;
       size_t size  = 0;
       size_t workGroupSize= 0;
       cl_uint maxClockFreq = 0;
       cl_uint maxWorkItemDim = 0;
       cl_ulong maxMemSize = 0;
       cl_ulong maxGlobalMemSize = 0;
       cl_ulong maxGlobalCache = 0;
       cl_ulong maxConstantBufferSize = 0;
       cl_uint maxConstantArgs = 0; 
       cl_ulong maxLocalMemSize = 0;
       size_t image2DHeight = 0;
       size_t image2DWidth = 0;
       size_t image3DWidth = 0;
       size_t image3DHeight = 0;
       size_t image3Depth = 0;
       cl_int err = CL_SUCCESS;
       cl_uint maxComputeUnits = 0;
       cl_device_id deviceID[numDevices];
       size_t maxWorkItemSize[3]= {0};
  
       err = clGetDeviceIDs(platform, deviceType, 0, NULL, &numDevices);
       if (CL_SUCCESS != err)
       {
           return 1;
       } 
       err = clGetDeviceIDs(platform, deviceType, numDevices, deviceID, NULL);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesID error"<<endl;
           return 1;
       } 
  
       printf("numDevices is : %d\n",numDevices);
       device = deviceID[0];
       err = clGetDeviceInfo(device, CL_DEVICE_NAME,0, NULL, &size);
       if (CL_SUCCESS != err)
       {
           return 1;
       } 
  
       vector<char> DeviceName(size);
       err = clGetDeviceInfo(device, CL_DEVICE_NAME, size, &DeviceName[0], NULL);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesname error"<<endl;
           return 1;
       } 
  
       printf("Device Name                         : %s\n", &DeviceName[0]);
  
       err = clGetDeviceInfo(device,CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint), &maxComputeUnits, &size);
       if (CL_SUCCESS != err)
       {
            cout<<"Error:query devicesunit error"<<endl;
            return 1;
       } 
  
       printf("\tDevice Compute Unit                 : %d\n", maxComputeUnits);
  
       err = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(cl_uint), &maxClockFreq, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesfrequency error"<<endl;
           return 1;
       } 
  
       printf("\tDevice Max Clock Frequency          : %dMhz\n", maxClockFreq);
  
       err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint), &maxWorkItemDim, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesitemdim error"<<endl;
           return 1;
       }
  
       printf("\tDevice Max Work Item Dimension Unit : %d\n",maxWorkItemDim);

       err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES,sizeof(size_t) * 3, maxWorkItemSize, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesitemsize error"<<endl;
           return 1;
       }
  
       printf("\tDevice Max Work Item Size           : (%d, %d, %d)\n",maxWorkItemSize[0], maxWorkItemSize[1], maxWorkItemSize[2]);

       err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &workGroupSize, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesgroupsize error"<<endl;
           return 1;
       }

       printf("\tDevice Work Group Size              : %d\n",workGroupSize);
  
       err = clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &maxMemSize, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesallocsize error"<<endl;
           return 1;
       }  
  
       printf("\tDevice Max Memmory Size             : %lu(bytes)\n", maxMemSize);
  
       err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &maxGlobalMemSize, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicesmemsize error"<<endl;
           return 1;
       } 
       printf("\tDevice Global Memory Size           : %lu(bytes)\n", maxGlobalMemSize);
  
       err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cl_ulong), &maxGlobalCache, &size);
       if (CL_SUCCESS != err)
       {
           cout<<"Error:query devicescachesize error"<<endl;
           return 1;
       }   
  
        printf("\tDevice Global CacgeMemory Size      : %lu(bytes)\n", maxGlobalCache);
  
        err = clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong), &maxConstantBufferSize, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query devicesbuffersize error"<<endl;
           return 1;
        }
  
        printf("\tDevice Max Constant Buffer Size     : %lu(bytes)\n", maxConstantBufferSize);
  
        err = clGetDeviceInfo(device, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(cl_uint), &maxConstantArgs, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query devicesargssize error"<<endl;
           return 1;
        }   
  
        printf("\tDevice Max Constant Aruguments      : %d\n", maxConstantArgs);
  
        err = clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &maxLocalMemSize, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query deviceMEMsize error"<<endl;
           return 1;
        }  
  
        printf("\tDevice Local Mem Size               : %lu(bytes)\n", maxLocalMemSize);
  
        err = clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size_t), &image2DWidth, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query deviceIMAGE2Dwidth error"<<endl;
           return 1;
        }   
  
        printf("\tDevice 2D Image Max Width           : %d\n", image2DWidth);
  
        err = clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size_t), &image2DHeight, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query deviceIMAGE2Dhight error"<<endl;
           return 1;
        }
  
        printf("\tDevice 2D Image Max Height          : %d\n", image2DHeight);
  
        err = clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size_t), &image3DWidth, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query deviceIMAGE3Dwidth error"<<endl;
           return 1;
        }   
  
        printf("\tDevice 3D Image Max Width           : %d\n", image2DWidth); 
  
        err = clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size_t), &image3DHeight, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query deviceIMAGE3Dhight error"<<endl;
           return 1;
        }
  
        printf("\tDevice 3D Image Max Height          : %d\n", image3DHeight);

        err = clGetDeviceInfo(device, CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size_t), &image3Depth, &size);
        if (CL_SUCCESS != err)
        {
           cout<<"Error:query deviceIMAGE3Ddepth error"<<endl;
           return 1;
        }

        printf("\tDevice 3D Image Max Depth           : %d\n", image3Depth);

        return 0;
   }
   
   int startup::Create_Context_Transfer()
   {
        cl_int err = CL_SUCCESS;
        cl_device_type deviceType = CL_DEVICE_TYPE_GPU;
        size_t deviceBufferSize=0;

        cl_context_properties contextProperties[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0};
        context = clCreateContextFromType(contextProperties, deviceType, NULL, NULL, &err);
        if((CL_SUCCESS != err) || (NULL == context))
        {
           context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU, NULL, NULL, &err);
           std::cout<<"Error:Couldn't create a GPU context but creat CPU context\n"<<std::endl;
           return 1;
        }
   
        err = clGetContextInfo(context, CL_CONTEXT_DEVICES, sizeof(cl_device_id), &device, NULL);
        if (CL_SUCCESS != err)
        {
           std::cout<<"Error: clGetContextInfo() to get list of devices returned\n"<<std::endl;
           return 1;
        }
  
        commandQueue = clCreateCommandQueue(context, device, 0,NULL);
        if(commandQueue == NULL)
        {
           std::cout<<"Error:Failed to create commandQueue for device 0"<<std::endl;
	       return 1;
        }
  
        return 0;
   }
   
   int startup::Create_Kernel_Method(char *filename)
   {
       cl_int err = CL_SUCCESS;
       size_t datasize;
    
       ifstream kernelFile(filename, std::ios::in);
  
       if (!kernelFile.is_open())
       {
          std::cout << "Failed to open file for reading: " << filename << std::endl;
          return 1;
       }
  
       std::ostringstream oss;
       oss << kernelFile.rdbuf();//oss输出kernelFile指向的流缓冲
       std::string srcStdStr = oss.str();
       const char *srcStr = srcStdStr.c_str(); 
       size_t sourceSize[]    = { strlen(srcStr) };
  
       //在context上下文上创建程序对象(字符串个数为1)
       program = clCreateProgramWithSource(context, 1, (const char**)&srcStr,sourceSize, &err);
       if(program == NULL)
       {
          std::cout << "Failed to create CL program from source." << std::endl;
          return 1;
       }
  
       err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);                       //program kernel source code
       if(CL_SUCCESS != err)
       {
          char buildLog[16384];
          clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,sizeof(buildLog), buildLog, NULL);
          std::cout << "Error in kernel: " << buildLog << std::endl;
          clReleaseProgram(program);                                               //relese program space
          return 1;
       }

       return 0;
   }
   
   bool startup::Create_Mem_Object(float *a,float *b)
   {
         memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,sizeof(float) * ARRAY_SIZE, a, NULL);
         memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,sizeof(float) * ARRAY_SIZE, b, NULL);
         memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,sizeof(float) * ARRAY_SIZE, NULL, NULL);
 
         if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL)
         {
            std::cout << "Error creating memory objects." << std::endl;
            return false;
         }
 
       return true;
   }
   
   void startup::Cleanup()
   {
       for (int i = 0; i < 3; i++)
       {
          if (memObjects[i] != 0)
            clReleaseMemObject(memObjects[i]);
       }
       if (commandQueue != 0)
           clReleaseCommandQueue(commandQueue);
 
       if (kernel != 0)
           clReleaseKernel(kernel);
 
       if (program != 0)
           clReleaseProgram(program);
 
       if (context != 0)
           clReleaseContext(context);
   }
   
   int startup::Mem_Write_Kernel(char *filename)
   {
      cl_int err = CL_SUCCESS;
	  kernel=clCreateKernel(program, "test_kernel", NULL);
	  if(kernel == NULL)
	  {
	     std::cout << "Failed to create kernel" << std::endl;
         startup::Cleanup();
         return 1;
	  }
	  
      float a[ARRAY_SIZE];
      float b[ARRAY_SIZE];
      for (int i = 0; i < ARRAY_SIZE; i++)
      {
          a[i] = (float)i;
          b[i] = (float)(2*i);
      }
	  
	  if (!startup::Create_Mem_Object(a,b))                                      //create kernel class
      {
         startup::Cleanup();
         return 1;
      }
	  
	  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
      err |=clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
      err |=clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);//set kernel parameter
	
      if (err != CL_SUCCESS)
      {
          std::cout << "Error setting kernel arguments." << std::endl;
          startup::Cleanup();
          return 1;
      }
	  
	  size_t globalWorkSize[1] = { ARRAY_SIZE };
      size_t localWorkSize[1] = { 1 };
	
	  err =clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	  if(err != CL_SUCCESS)
	  {
	  
          std::cout << "Error queuing kernel for execution." << std::endl;
          startup::Cleanup();
          return 1;
	  }
   }
   
   int startup::Mem_Read_Kernel()
   {
      cl_int err = CL_SUCCESS;
	  float result[ARRAY_SIZE];
	  err = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE,0, ARRAY_SIZE * sizeof(float), result,0, NULL, NULL);
	  if(err != CL_SUCCESS)
	  {
	  
          std::cout << "Error reading result buffer." << std::endl;
          startup::Cleanup();
          return 1;
	  }
	
	
      for (int i = 0; i < ARRAY_SIZE; i++)
      {
          std::cout << result[i] << " ";
      }
      std::cout << std::endl;
      std::cout << "Executed program succesfully." << std::endl;
      startup::Cleanup();
   }
   
}
