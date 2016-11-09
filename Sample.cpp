#include <jni.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

// https://neugens.wordpress.com/2015/02/26/debugging-the-jdk-with-gdb/
// https://code.visualstudio.com/docs/editor/debugging#_variable-substitution
// https://github.com/Microsoft/vscode-cpptools/blob/master/launch.md
// -exec handle SIGSEGV nostop noprint pass
extern int main(int argc, char** argv)
{
  JavaVMOption options[1];
  JNIEnv *env;
  JavaVM *jvm;
  JavaVMInitArgs vm_args;
  long status;
  jclass cls;
  jmethodID mid;
  jint square;
  jboolean notb;

  std::cout << getenv("JAVA_HOME") << std::endl;

  options[0].optionString = const_cast<char*>("-Djava.class.path=.");
  memset(&vm_args, 0, sizeof(vm_args));
  vm_args.version = JNI_VERSION_1_2;
  vm_args.nOptions = 1;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = JNI_FALSE;
  status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

  if (status != JNI_ERR)
  {
    cls = env->FindClass("Sample");
    if(cls !=0)
    {   mid = env->GetStaticMethodID(cls, "intMethod", "(I)I");
        if(mid !=0)
        {  square = env->CallStaticIntMethod(cls, mid, 5);
           printf("Result of intMethod: %d\n", square);
        }

        mid = env->GetStaticMethodID(cls, "booleanMethod", "(Z)Z");
        if(mid !=0)
        {  notb = env->CallStaticBooleanMethod(cls, mid, 1);
           printf("Result of booleanMethod: %d\n", notb);
        }
    }

    jvm->DestroyJavaVM();
   return 0;
  }
  else
    return -1;
}
