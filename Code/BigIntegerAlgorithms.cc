#include "BigIntegerAlgorithms.hh"
#include "BigUnsigned.hh"
#include "BigIntegerUtils.hh"
#include "BigInteger.hh"
#include "BigUnsignedInABase.hh"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;


BigUnsigned BigInt_Random(int lenght){
    BigUnsigned kq;
    string s1 ="9";
    for(int i =1;i<=lenght-1;i++){
        s1.push_back(9+48);
    }
   // cout << s1<<endl;
    int len = lenght;
    string result = s1;
        for(int i = len-1;i>=0;i--){
            int inr=0;
            int res_rand=0;
            inr = s1[i]-48;
            res_rand = random(0,inr);
            result[i]=res_rand+48;
        }
        kq =stringToBigUnsigned(result);


   return kq;

}

int random(int a,int b){
    int kq;
    kq= rand() % (b-a+1)+ a;
    return kq;
}

BigInteger BigInt_Random1(int leng)
{
    BigInteger kq;
    string s1 ="9";
    for(int i =1;i<=leng-1;i++){
        s1.push_back(9+48); // chuyen ve char
    }
    int len = leng; // số chữ số của số đó vd = 3 =>> 999 , vd = 7 =>> 9999999
    string result = s1;
        for(int i = len-1;i>=0;i--){
            int inr=0;
            int res_rand= 0 ;
            inr = s1[i]-48;
            res_rand = random(0,inr);
            result[i]= res_rand + 48; // chuyen ve char
        }

        kq = stringToBigInteger(result); // convert kiểu string sang kiểu BigInt
   return kq;
}

BigUnsigned gcd(BigUnsigned a, BigUnsigned b) {

    while(!(b.isZero())){
        BigUnsigned r=a%b;
        a=b;
        b=r;
    }
    return a;
}

BigInteger gcd(BigInteger a,BigInteger b){ //BigInteger


    BigInteger temp(0);

    while(!(b.isZero())){

        BigInteger r=a%b;
        a=b;
        b=r;

    }
    return a;
}

BigInteger pow(BigInteger a,BigInteger n) // Power BigInteger
{
    BigInteger one(1);
    BigInteger two(2);
    BigInteger zero(0);
    if(n==zero){
        return one;
    }
    if(n == one) {
        return a;
    } else {
        BigInteger temp = pow(a,n/two);
        if(n % two == zero){

            return temp * temp;
        }
        else
            return temp * temp * a;
    }

}

BigUnsigned pow(BigUnsigned a,BigUnsigned n) // Power BigInteger Unsigned
{

    BigUnsigned one(1);
    BigUnsigned two(2);
    BigUnsigned zero(0);

    if(n==zero){
        return one;
    }
    if(n == one) {
        return a;
    } else {
        BigUnsigned temp = pow(a,n/two);
        if(n % two == zero){

            return temp * temp;
        }
        else
            return temp * temp * a;
    }
}



BigInteger a_powx_modn(BigInteger x,BigInteger b,BigInteger n){ // BigInteger

    BigInteger a;
    a=x;
    BigInteger y(1);
    BigInteger z(2);
    BigInteger zero(0);
    do{
        if((b%z)!=zero){
            y = y*a;
            y = y % n;
        }
        b = b/z; // dịch các bít 1 sang phải b = b shr 1;

        a= a*a;

        a=a%n;
    }while(b>zero);

    return y;
}



BigUnsigned a_powx_modn(BigUnsigned x,BigUnsigned b,BigUnsigned n){ // BigInteger

    BigUnsigned a;
    a=x;
    BigUnsigned y(1);
    BigUnsigned z(2);
    BigUnsigned zero(0);
    do{
        if((b%z)!=zero){
            y = y*a;
            y = y % n;
        }
        b = b/z;
        a= a*a;
        a=a%n;
    }while(b>zero);

    return y;
}
BigInteger Mod_Inverse(BigInteger e,BigInteger phi){

    BigInteger temp;
    BigInteger d(1) , yphi(0);
    BigInteger q,xr,r;

    temp = phi;

    while(phi>0){
        q = e / phi;
        xr = d - q *  yphi;
        d = yphi;
        yphi = xr;
        r = e % phi;
        e = phi;
        phi =  r;
    }

    if(d<0) return (temp + d);
    else
    return d;

}

BigUnsigned Mod_Inverse(BigUnsigned e,BigUnsigned phi){

    string temp1;

    BigInteger e1,phi1;
    temp1 = bigUnsignedToString(e);
    e1 = stringToBigInteger(temp1);
    temp1 = bigUnsignedToString(phi);
    phi1 = stringToBigInteger(temp1);
    BigInteger temp;
    BigInteger d(1) , yphi(0);
    BigInteger q,xr,r;

    temp = phi1;

    while(phi1>0){

        q = e1 / phi1;
        xr = d - q *  yphi;
        d = yphi;
        yphi = xr;
        r = e1 % phi1;
        e1 = phi1;
        phi1 =  r;

    }
    BigUnsigned kq;
    if(d<0) {
        temp1 = bigIntegerToString(temp +d);
        kq = stringToBigUnsigned(temp1);
        return kq;
    }
    else{
        temp1 = bigIntegerToString(d);
        kq = stringToBigUnsigned(temp1);
        return kq;
    }


}

BigUnsigned get_q(BigUnsigned a){

    BigUnsigned k;
    k=0;
    a=a-1;
    while(a % 2 == 0){
        a = a/2;
        k = k + 1;
    }

    return a;
}
BigUnsigned get_k(BigUnsigned a){

    BigUnsigned k;
    k=0;
    a=a-1;
    while(a % 2 == 0){
        a = a/2;
        k = k + 1;
    }

    return k;
}
int Miller_Rabin(BigUnsigned p,int loop){ // kiểm tra số P với biến loop là số lần lặp tùy ý

    if(p==1||p==2){
        return 1;
    }
    BigUnsigned k,q,a,two;
    two=2;
    string s_t;
    s_t = bigUnsignedToString(p-1);
    q=get_q(p);
    k=get_k(p);

    int count_false = 0;
    int count_true = 0;
    for(int i = 0;i<loop;i++){
        do{
            a=BigInt_Random(s_t.length());
        }while((a<2)||(a>p-1));
        if(a_powx_modn(a,q,p) == 1 ){
            count_true++;
        }
        else
        {
           for(BigUnsigned j = 0 ;j < k ;j++){
               BigUnsigned pow_val;
               pow_val = pow(two,j);
               if(a_powx_modn(a,pow_val*q,p)==p-1){
                   count_true++;
               }
           }
        }
        count_false++;
    }
    if(count_true == loop){
        return 1;
    }
    if(count_false > 0){
        return 0;
    }
}

string DectoHex(BigUnsigned a){
    BigUnsigned mod,temp;
    string res,res1;
    if(a==0){
        return res1 ="0";
    }
    while(a>0){
        mod = a%16;
        int mod_int = mod.toInt();
        a = a/16;
        switch (mod_int) {
            case 0:{
                res.push_back(0+48);
                break;
            }
            case 1:{
                res.push_back(1+48);
                break;
            }
            case 2:{
                res.push_back(2+48);
                break;
            }
            case 3:{
                res.push_back(3+48);
                break;
            }
            case 4:{
                res.push_back(4+48);
                break;
            }
            case 5:{
                res.push_back(5+48);
                break;
            }
            case 6:{
                res.push_back(6+48);
                break;
            }
            case 7:{
                res.push_back(7+48);
                break;
            }
            case 8:{
                res.push_back(8+48);
                break;
            }
            case 9:{
                res.push_back(9+48);
                break;
            }
            case 10:{
                res.push_back('a');
                break;
            }
            case 11:{
                res.push_back('b');
                break;
            }
            case 12:{
                res.push_back('c');
                break;
            }
            case 13:{
                res.push_back('d');
                break;
            }
            case 14:{
                res.push_back('e');
                break;
            }
            case 15:{
                res.push_back('f');
                break;
            }
            default:
                break;
        }
    }

    for(int i=res.length()-1;i>=0;i--){
        res1.push_back(res[i]);
    }
    return res1;
}

BigUnsigned HextoDec(string str){

    BigUnsigned Hex,result;
    Hex=16;
    result =0;
    string rev_str;
    for(int i = str.length()-1;i>=0;i--){
        rev_str.push_back(str[i]);
    }
    for(int i= rev_str.length()-1;i>=0;i--){
        switch (rev_str[i]) {
            case '0':{
                result = result + ((pow(Hex,i)*0));
                break;
            }
            case '1':{
                result = result + ((pow(Hex,i)*1));
                break;
            }
            case '2':{
                result = result + ((pow(Hex,i)*2));
                break;
            }
            case '3':{
                result = result + ((pow(Hex,i)*3));
                break;
            }
            case '4':{
                result = result + ((pow(Hex,i)*4));
                break;
            }
            case '5':{
                result = result + ((pow(Hex,i)*5));
                break;
            }
            case '6':{
                result = result + ((pow(Hex,i)*6));
                break;
            }
            case '7':{
                result = result + ((pow(Hex,i)*7));
                break;
            }
            case '8':{
                result = result + ((pow(Hex,i)*8));
                break;
            }
            case'9':{
                result = result + ((pow(Hex,i)*9));
                break;
            }
            case 'a':{
                result = result + ((pow(Hex,i)*10));
                break;
            }
            case 'b':{
                result = result + ((pow(Hex,i)*11));
                break;
            }
            case 'c':{
                result = result + ((pow(Hex,i)*12));
                break;
            }
            case 'd':{
                result = result + ((pow(Hex,i)*13));
                break;
            }
            case 'e':{
                result = result + ((pow(Hex,i)*14));
                break;
            }
            case 'f':{
               result = result + ((pow(Hex,i)*15));
                break;
            }
            default:
                break;
        }
    }
            return result;
}

void extendedEuclidean(BigInteger m, BigInteger n,
		BigInteger &g, BigInteger &r, BigInteger &s) {
	if (&g == &r || &g == &s || &r == &s)
		throw "BigInteger extendedEuclidean: Outputs are aliased";
	BigInteger r1(1), s1(0), r2(0), s2(1), q;
	/* Invariants:
	 * r1*m(orig) + s1*n(orig) == m(current)
	 * r2*m(orig) + s2*n(orig) == n(current) */
	for (;;) {
		if (n.isZero()) {
			r = r1; s = s1; g = m;
			return;
		}
		// Subtract q times the second invariant from the first invariant.
		m.divideWithRemainder(n, q);
		r1 -= q*r2; s1 -= q*s2;

		if (m.isZero()) {
			r = r2; s = s2; g = n;
			return;
		}
		// Subtract q times the first invariant from the second invariant.
		n.divideWithRemainder(m, q);
		r2 -= q*r1; s2 -= q*s1;
	}
}

BigUnsigned modinv(const BigInteger &x, const BigUnsigned &n) {
	BigInteger g, r, s;
	extendedEuclidean(x, n, g, r, s);
	if (g == 1)
		// r*x + s*n == 1, so r*x === 1 (mod n), so r is the answer.
		return (r % n).getMagnitude(); // (r % n) will be nonnegative
	else
		throw "BigInteger modinv: x and n have a common factor";
}

BigUnsigned modexp(const BigInteger &base, const BigUnsigned &exponent,
		const BigUnsigned &modulus) {
	BigUnsigned ans = 1, base2 = (base % modulus).getMagnitude();
	BigUnsigned::Index i = exponent.bitLength();
	// For each bit of the exponent, most to least significant...
	while (i > 0) {
		i--;
		// Square.
		ans *= ans;
		ans %= modulus;
		// And multiply if the bit is a 1.
		if (exponent.getBit(i)) {
			ans *= base2;
			ans %= modulus;
		}
	}
	return ans;
}


