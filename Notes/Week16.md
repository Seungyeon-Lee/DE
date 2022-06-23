# 6주차 (22. 06. 14)
[Notion Link](https://www.notion.so/6-22-06-14-8bbc857d8a8c4b28a50654f87ff21667)

### RenderCommandEncoder

CommandList가 하는 일을 맡아서 해준다.

Rendering Command 넣을 때 RenderTarget, 명령어 넣는 방식.

명령어를 넣을 때마다 상태가 바뀌는데 Encoder에서 이런 부분을 관리해줄 수 있다.

예시로 Encoder에 리스트를 잔뜩 들고 있다가 Buffer에 한꺼번에 넘기는 방식으로도 활용 가능.

### Command Buffer (=Command List)

Encoder = Metal 구조. 

DirectX에선 큰 이점을 갖진 못하지만 Vulkan에선 많은 이득을 볼 수 있다. (유연한 구조적 이점)

Texture 하나당 Heap 하나씩 갖고 있는 형태.

scissorRect : 그려질 부분만 잘라서 그린다.

fence : 타임라인 기반. 명령어가 들어간 순간을 fence. 다 끝나고 나서 signal을 보내준다.

### Texture.h에서 dynamic_cast를 사용하는 이유

순수 가상함수 외에 정의된 함수를 사용하기 위해서 상위 뷰에서 하위뷰로 캐스팅하기 위해 사용. (rtti 사용 시 가능. rtti를 사용하지 못하는 경우 + 어떤 타입인지 명확한 경우에 포인터 타입을 변환해주는 캐스팅인 reinterpret_cast를 사용하는 것으로 대체가 가능)

tuple 만들어보면 템플릿 메타 프로그래밍은 충분히 학습 가능.