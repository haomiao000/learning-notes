void discreate1()
{
	sort(a1+1 , a1+n+1);
	for(int i=1;i<=n;i++)
		if(i==1||a1[i]!=a1[i-1])
			b1[++m1]=a1[i];
}