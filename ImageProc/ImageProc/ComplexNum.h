typedef struct cnode
{
	double real;
	double imag; //imaginary ÐéÊý²¿·Ö
	cnode() :real(0), imag(0){}
	cnode(double r, double i) :real(r), imag(i){}
}ComplexNum;
ComplexNum operator* (ComplexNum const & c1, ComplexNum const & c2)
{
	ComplexNum result;
	result.real = c1.real * c2.real - c1.imag * c2.imag;
	result.imag = c1.real * c2.imag + c1.imag * c2.real;
	return result;
}
ComplexNum operator+ (ComplexNum const & c1, ComplexNum const & c2)
{
	ComplexNum result;
	result.real = c1.real + c2.real;
	result.imag = c1.imag + c2.imag;
	return result;
}
ComplexNum operator- (ComplexNum const & c1, ComplexNum const & c2)
{
	ComplexNum result;
	result.real = c1.real - c2.real;
	result.imag = c1.imag - c2.imag;
	return result;
}