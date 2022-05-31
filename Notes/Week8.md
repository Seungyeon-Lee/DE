# 8주차 (22. 02. 07)
[Notion Link](https://www.notion.so/8-22-02-07-99ea470dd721482da0e549b0b0dcbf35)

### Vertex Buffer

정점 리스트

Vertex Buffer를 GPU에 올려야하는데 정점 버퍼 역시 Resource이다.

옵션 중 Dimension이 있는데, 이때 Buffer Dimension을 사용하면 된다.

앞에 C 가 붙는 함수들은 버퍼를 위한 편의 함수이다. 

### Upload Buffer

GPU 자원은 활용도에 따라서 3가지 정도로 분류된다.

D3D12_HEAP_TYPE_DEFAULT는 GPU에서만 읽을 수 있고,

D3D12_HEAP_TYPE_UPLOAD는 CPU에서 GPU로 보내기 위한 속성이며,

D3D12_HEAP_TYPE_READBACK는 GPU 자원을 CPU로 읽는 속성이다.

CPU에 있는 메모리를 GPU에 올리려면 Upload Buffer를 써야 한다.

Upload Buffer에 CPU 데이터인 정점 정보를 작성하고 CommandList를 사용하여 Upload Buffer의 데이터를 Default Buffer로 옮겨주는 작업을 한다. 복사가 완료되기 전까지는 Upload Buffer는 해제되면 안 된다.

## Input layout description

Vertex 전용 Descriptor

Vertex Buffer를 Render Pipeline에 쓸 것이다라고 선언.

GPU에 Position과 Color가 있다고 알려주는 역할을 한다.

Shader를 판별할 수 있게 하기 위해서 Semantic하다.

OpenGL의 GLSL은 Semantic이 필요 없다.

GPU에 레이아웃을 설명해주어야 할 때 사용한다.

Semantic 순서와 레이아웃 정의 순서가 동일해야 한다.

### Constant Buffer

매 프레임 바뀌는 경우가 많다.

CPU에서 값을 쓸 수 있게 하기 위해서 Heap을 Upload 타입으로 만든다.

주의점 : 메모리 단위가 256바이트의 배수여야 생성이 가능하다. 따라서 직접 Align해서 넘겨주어야 한다.

GPU자원이기 때문에 Descriptor가 필요하다.

제일 중요한 것은 Shader에 어떠한 Resource가 바인딩되는 지 적어줘야 한다.

### Root Signature

Root Descriptor Table : Heap에 바인딩할 때 여러 개를 담아둘 수 있는 것.

### **Shader를 Compile을 해야 하는 이유**

- 최적화(바이트로 바꾸면서 메모리가 줄어들기도 한다)
- 보안 문제

### Rendering Pipeline

DX12부터 Rendering Pipeline을 Custom 할 수 있다.

Rendering Pipeline에서 실제로 일어날 일을 정의한다.

Input Layout이 조금이라도 바뀌면 전부 다 바뀌어야 한다.

그래서 보통 돌려가면서 쓸 수 있도록 Shader를 만든다.

Vertex Buffer를 만든다.

Rendering을 하기 위해서는 RenderTarget이 필요하므로,

Descriptor Table을 등록해주고 그려준다.

CommandList를 GPU Queue에 넣어주고 순차적으로 실행시킨다.

완료되면 Back Buffer를 화면에 출력한다.

카메라를 만든 게 아니라 마우스 위치를 정해서 보여준다.

Draw를 한 번만 하는 케이스가 아니라면 Deferred Rendering은 필수로 작업해야 한다.