#include <iostream>
#include <stdexcept>

class Test {
public:
	Test(char id) : id_(id) {}
	~Test() { std::cout << "Destructor execution: " << id_ << std::endl; }
private:
	char id_;
};

int funcB() {
	Test r('B');
	throw std::runtime_error("Exception from funcB!\n");
	std::cout << "Executed in B" << std::endl;
	return 0;
}

int funcA() {
	Test a('A');
	funcB();
	std::cout << "Executed in A" << std::endl;
	return 0;
}

int main() {
	try {
		funcA();
	}
	catch(std::exception& e){
		std::cout << "Exception : " << e.what();
	}
}

/* (실습 1-1) 분석결과 : 

일단, Test에 쓰일 Class Test를 정의한다. 
이 클래스는 char형 인스턴스 변수 _id를 가지고 있으며, 
생성자에서 인자로 char형 데이터를 전달받으면 이 값을 _id에 할당한다.
소멸자의 경우, "Destructor execution : "이라는 문자열을 출력하며, 어떤 객체가 소멸되는지 뒤에 _id 값을 출력한다.

함수 funcA()는 Test 클래스의 객체를 생성하며 _id값을 A로 설정한다
다음으로 함수 내에서 또다른 함수 funcB() 함수를 호출한다.
funcB() 함수가 종료되면 funcA 함수가 실행되었다는 메시지를 cout 객체를 통해 출력하고 
0을 리턴하면서 함수를 종료한다.

함수 funcB()는 funcA 함수와 거의 비슷한 기능을 수행한다.
일단 throw 구문은 주석 처리하였기 때문에 이는 실행되지 않을 것이며,
함수 funcB 함수가 실행되었다는 메시지를 cout 객체를 통해 출력하고 
0을 리턴하면서 함수를 종료한다.

main 함수는 try 구문안에서 funcA 함수를 실행하며 이곳에서 예외를 감지하면
catch 구문에 예외 인자를 전달하여 예외 객체의 내용을 출력한다.

실행 결과를 분석해보면 일단 main 함수에서 funcA 함수를 실행하고, funcA 함수 내에서 funcB 함수를 호출했다.
funcB 함수에서 오류 없이 모든 기능이 수행되었기 때문에 "Executed in B" 문자열을 출력한다.
또한, 함수가 종료되었으므로 객체도 소멸자를 호출하여 "Destructor execution: B" 문자열을 출력한다.
funcB 함수의 실행이 끝났으므로 funcA의 기능이 수행된다. 
이번에도 별 이상없이 기능이 수행되었으므로 "Executed in A" 문자열을 출력한다.
마찬가지로 funcA 함수가 종료되었기 때문에 객체가 소멸자를 호출하여 "Destructor execution: A" 문자열을 출력한다./




/* (실습 1-2) 분석결과 :

위에서는 throw 구문을 주석처리했지만, 주석처리를 해제했을 경우를 분석한다.
그렇다면 함수 funcB 에서 runtime_error 예외를 throw하게 된다.
하지만, funcB 함수에서는 예외를 처리할 수 있는 방법이 없기 때문에 funcB 함수를 함수 스택에서 제거한다.
이 과정에서 함수 내에서 생성된 Test 객체의 소멸자를 호출한다. 따라서, "Destructor execution: B" 문자열을 출력한다.
그리고 funcB 함수 바로 전에 호출됐던 funcA 함수로 돌아가지만 마찬가지로 예외를 처리할 수 있는 방법이 구현되어있지 않다.
따라서 funcA 함수도 스택에서 제거하며, 생성된 객체에 대한 소멸자를 호출해 "Destructor execution: A" 문자열을 출력한다.
결국 맨 처음 수행된 main 함수로 돌아왔으며 main 함수에서는 catch문이 존재하기 때문에 예외를 처리할 수 있다.
따라서 이에 맞게 funcB에서 전달된 예외를 처리하는 과정을 거쳐 "Exception : Exception from funcB!" 문자열을 출력한다.

이와 같이 예외가 발생했을 때, 적절한 처리 방법이 구현되어있지 않으면 현재 실행되고 있는 함수들이 쌓여있는 스택을 되짚어 
확인하는 방법을 Stack Unwinding 이라고 한다.*/
