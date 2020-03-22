
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phra-runner.h"

#include "angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "angelscript/add_on/scriptbuilder/scriptbuilder.h"

// Print the script string to the standard output stream
void print(std::string &msg)
{
  printf("%s", msg.c_str());
}

void PHRA_Runner::message_callback(const asSMessageInfo* msg, void* param)
{
 const char *type = "ERR ";
 if( msg->type == asMSGTYPE_WARNING ) 
   type = "WARN";
 else if( msg->type == asMSGTYPE_INFORMATION ) 
   type = "INFO";
 printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message); 
}

PHRA_Runner::PHRA_Runner()
{
  // Create the script engine
 engine_ = asCreateScriptEngine();
 
 int r = engine_->SetMessageCallback(asFUNCTION(&PHRA_Runner::message_callback), 0,  asCALL_CDECL); 
 assert( r >= 0 );
 
 RegisterStdString(engine_);
 
 // Register the function that we want the scripts to call 
 r = engine_->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL); 
 assert( r >= 0 );


}

void PHRA_Runner::run_script(QString path)
{
 CScriptBuilder builder;
 int r1 = builder.StartNewModule(engine_, "MyModule"); 
 if( r1 < 0 ) 
 {
  // If the code fails here it is usually because there
  // is no more memory to allocate the module
  printf("Unrecoverable error while starting a new module.\n");
 }
 r1 = builder.AddSectionFromFile(path.toStdString().c_str()); //PHRA_ROOT_DIR "/test.as");
 if( r1 < 0 )
 {
  // The builder wasn't able to load the file. Maybe the file
  // has been removed, or the wrong name was given, or some
  // preprocessing commands are incorrectly written.
  std::printf("Please correct the errors in the script and try again.\n");
 }
 r1 = builder.BuildModule();
 if( r1 < 0 )
 {
  // An error occurred. Instruct the script writer to fix the 
  // compilation errors that were listed in the output stream.
  printf("Please correct the errors in the script and try again.\n");
 }

 // Find the function that is to be called. 
 asIScriptModule *mod = engine_->GetModule("MyModule");
 asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
 if( func == 0 )
 {
  // The function couldn't be found. Instruct the script writer
  // to include the expected function in the script.
  printf("The script must have the function 'void main()'. Please add it and try again.\n");
 }
 
 // Create our context, prepare it, and then execute
 asIScriptContext *ctx = engine_->CreateContext();
 ctx->Prepare(func);
 int rr = ctx->Execute();
 if( rr != asEXECUTION_FINISHED )
 {
  // The execution didn't complete as expected. Determine what happened.
  if( rr == asEXECUTION_EXCEPTION )
  {
   // An exception occurred, let the script writer know what happened so it can be corrected.
   std::printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
  }
 }
 ctx->Release();
}

PHRA_Runner::~PHRA_Runner()
{
 // Clean up
 engine_->ShutDownAndRelease();
}


#ifdef HIDE
#include <QDebug>
#include <QFile>
// Include the definitions of the script library and the add-ons we'll use.
// The project settings may need to be configured to let the compiler where
// to find these headers. Don't forget to add the source modules for the
// add-ons to your project as well so that they will be compiled into the 
// application.
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

void print(std::string &msg);

// Implement a simple message callback function
void MessageCallback(const asSMessageInfo *msg, void *param)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING ) 
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION ) 
    type = "INFO";
  printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

int main(int argc, char* argv[])
{
 // Create the script engine
 asIScriptEngine *engine = asCreateScriptEngine();
 
 // Set the message callback to receive information on errors in human readable form.
 int r = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0,  asCALL_CDECL); assert( r >= 0 );
 
 // AngelScript doesn't have a built-in string type, as there is no definite standard 
 // string type for C++ applications. Every developer is free to register its own string type.
 // The SDK do however provide a standard add-on for registering a string type, so it's not
 // necessary to implement the registration yourself if you don't want to.
 RegisterStdString(engine);
 
 // Register the function that we want the scripts to call 
 r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL); assert( r >= 0 );

 // The CScriptBuilder helper is an add-on that loads the file,
 // performs a pre-processing pass if necessary, and then tells
 // the engine to build a script module.
 CScriptBuilder builder;
 int r1 = builder.StartNewModule(engine, "MyModule"); 
 if( r1 < 0 ) 
 {
  // If the code fails here it is usually because there
  // is no more memory to allocate the module
  printf("Unrecoverable error while starting a new module.\n");
  return 0;
 }
 r1 = builder.AddSectionFromFile(PHRA_ROOT_DIR "/test.as");
 if( r1 < 0 )
 {
  // The builder wasn't able to load the file. Maybe the file
  // has been removed, or the wrong name was given, or some
  // preprocessing commands are incorrectly written.
  std::printf("Please correct the errors in the script and try again.\n");
  return 0;
 }
 r1 = builder.BuildModule();
 if( r1 < 0 )
 {
  // An error occurred. Instruct the script writer to fix the 
  // compilation errors that were listed in the output stream.
  printf("Please correct the errors in the script and try again.\n");
  return 0;
 }

 // Find the function that is to be called. 
 asIScriptModule *mod = engine->GetModule("MyModule");
 asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
 if( func == 0 )
 {
  // The function couldn't be found. Instruct the script writer
  // to include the expected function in the script.
  printf("The script must have the function 'void main()'. Please add it and try again.\n");
  return 0;
 }
 
 // Create our context, prepare it, and then execute
 asIScriptContext *ctx = engine->CreateContext();
 ctx->Prepare(func);
 int rr = ctx->Execute();
 if( rr != asEXECUTION_FINISHED )
 {
  // The execution didn't complete as expected. Determine what happened.
  if( rr == asEXECUTION_EXCEPTION )
  {
   // An exception occurred, let the script writer know what happened so it can be corrected.
   std::printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
  }
 }

 // Clean up
 ctx->Release();
 engine->ShutDownAndRelease();

 return 0; 
}


// Print the script string to the standard output stream
void print(std::string &msg)
{
  printf("%s", msg.c_str());
}

#endif //def HIDE

