# 8주차 (22. 06. 29)
[Notion Link](https://www.notion.so/8-22-06-29-f5328f81c0914790bd7dabfaa5e7e09c)

## Camera

우리가 바라보는 시점 ⇒ 카메라

카메라 위치정보(view transform), 카메라 방향 정보 or target

바라보는 방향과 world를 기준으로 내적/외적한다.

물체를 기준으로 시야 공간→세계 공간으로 변환하는 행렬을 얻는다.

스크린에 투명해주는 행렬projection matrix

0~1 사이로 정규화하기때문에 float 소수점으로 바뀌어지고 오차때문에 z-fighting이 일어난다.

reversed-z를 사용하는 것이 더 좋다.

z를 뒤집었으므로 초기화를 1대신 0으로 해주어야 한다.

left-bottom이 기존엔 원점이라 left top으로 옮기는 작업을 한다.

쉐이더는 Column-Based 행렬이라 뒤집혀서 들어간다.

메모리 읽는 방식이 다르다.

### primitive shader

나나이트nvidia

파이프라인을 효율적으로 재구성했다.

미리 컬링 가능한 방식.

선별적으로 사용할 자원만 올릴 수 있다. (훨씬 최적화가 잘 되어있다)