int main()
{

  double a = 101012.12;

  long long bits = *(long long *)(&a);

  return 0;
}