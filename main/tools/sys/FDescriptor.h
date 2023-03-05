namespace sys
{
	typedef int FDescriptor;

	extern FDescriptor nullFd;
	extern FDescriptor stdIn;
	extern FDescriptor stdOut;
	extern FDescriptor stdErr;

	bool validDescriptor(FDescriptor descriptor);
}