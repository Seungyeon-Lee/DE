# 5주차 (22. 06. 08)
[Notion Link](https://www.notion.so/5-22-06-08-9de60cdbbc2344d5942f42422364f265)

**CPython을 모놀리식으로 묶어서 사용하는 이유?**

묶지 않는 경우에는 모듈 별로 dll이 필요한데, 묶어서 하나의 dll을 생성하도록 만들어서 다른 dll들이 필요 없이 dll 하나만 있으면 사용할 수 있도록 함.

### Command Queue Type

DIRECT : Present, Copy-command 등 대부분의 연산을 할 때 사용.

COMPUTE : GPU에게 계산을 넘길 때 사용.

COPY : Copy 시 사용.

이렇게 타입이 나누어져 있는 이유는 병렬로 진행하기 위해서이다.

### Vulkan

**Opaque Data Type** : Object 포인터 덩어리

메모리 주소를 얻어와서 직접 호출해주어야 한다.

### 과제

drawCommand 보내기

- 색상 초기화 clear까지

GPU Buffer

- texture 포함
- Encoder-Buffer 구조로 변경.
    - commandList 구조도 맞춰서 변경
    - commandBuffer / Encoder
    

RenderCommandEncoder

- clearRenderTarget
- setRenderTarget