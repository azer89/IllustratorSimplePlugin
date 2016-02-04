
/**
 * Reza Adhitya Saputra
 * radhitya@uwaterloo.ca
 */

#include "IllustratorSDK.h"

// Xcode
#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif


// Plug-in entry point
extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message);

// Xcode
#if defined(__GNUC__)
#pragma GCC visibility pop
#endif


extern "C"
{
	AIUnicodeStringSuite* sAIUnicodeString = NULL; // error
	SPBlocksSuite* sSPBlocks = NULL;
}

extern "C" ASAPI ASErr PluginMain(char* caller, char* selector, void* message)
{
	ASErr error = kNoErr;

	SPBasicSuite* sSPBasic = ((SPMessageData*)message)->basic;
	if (sSPBasic->IsEqual(caller, kSPInterfaceCaller))
	{
		AIUserSuite *sAIuser = nil;

		error = sSPBasic->AcquireSuite(kAIUserSuite, kAIUserSuiteVersion, (const void**) &sAIuser);
		error = sSPBasic->AcquireSuite(kAIUnicodeStringSuite, kAIUnicodeStringVersion, (const void**) &sAIUnicodeString);
		error = sSPBasic->AcquireSuite(kSPBlocksSuite, kSPBlocksSuiteVersion, (const void**) &sSPBlocks);

		if (sSPBasic->IsEqual(selector, kSPInterfaceStartupSelector))
		{
			sAIuser->MessageAlert(ai::UnicodeString("Hello World, by Reza"));
		}
		else if (sSPBasic->IsEqual(selector, kSPInterfaceShutdownSelector))
		{
			sAIuser->MessageAlert(ai::UnicodeString("Goodbye, Life sucks"));
		}

		error = sSPBasic->ReleaseSuite(kAIUserSuite, kAIUserSuiteVersion);
		error = sSPBasic->ReleaseSuite(kAIUnicodeStringSuite, kAIUnicodeStringVersion);
	}

	return error;
}
