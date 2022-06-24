# 7주차 (22. 06. 21)
[Notion Link](https://www.notion.so/7-22-06-21-fbff336326f84af38cac2aa6b544313b)

### Render Pipeline

Shader 변경 가능하도록 Render Pipeline 하드코딩으로 생성.

### Copy Command Encoder

Upload Buffer 만들고 다른 데에 복사해야 하기 때문에 Copy Command Encoder가 필요하다.

CPU에서 조작할 수 있는 Upload Buffer를 GPU에 주기 위해서 사용한다.

(EX. Upload Buffer → Copy Buffer → Vertex Buffer)

GPU에 일 시키는 공정 = Render Pipeline

Shader에 어떤 자원이 Binding될지 보여진다.

blob : 원시 데이터

### Scoped Lock

Contex Switching 때 Switching하지 않고 기다린다.

잦은 Lock 사용의 경우 잠깐 기다리는 것이 더 성능에 유리하기 때문에 사용한다.

RAII 기법을 사용한 Lock. 소멸자에서 Unlock해준다.

### RAII (Resource Acquisition Is Initialization)

C++에서 자주 쓰이는 idiom으로 자원의 안전한 사용을 위해 객체가 쓰이는 스코프를 벗어나면 자원을 해제해주는 기법.

지역변수 개념.