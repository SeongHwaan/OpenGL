# SpaceSimulator 1.0

## 목적
- Low-Level Graphics API인 OpenGL 공부
- Modern OpenGL과 Shader 사용
- C++ 공부

## 1. 행성 구현
- 구(Sphere)를 구현하고 Texture mapping이 필요
- vertex 입력만으로 만드는 것에 어려움
- Assimp 라이브러리 사용해 Model 로드
- .obj와 .mtl에서 data 추출해 vertex buffer object에 저장
- 이후 Shader에서 어떻게 출력할지 결정

## 2. 중력 구현
- 만유인력의 법칙 사용

  <img src="https://github.com/user-attachments/assets/4a2dc782-4047-4eae-9e76-d19fab2536b1" height="480px" width="720px">


## 3. 꼬리(궤도) 구현
- 행성의 위치 데이터를 vector나 queue 자료형에 추가
- 위치 vertex를 저장하고 각 데이터를 GL_LINE_STRIP으로 출력
- 그러나 LINE이 의도대로 나오지 않는 오류 발생하여 POINTS로 구현

  <img src="https://github.com/user-attachments/assets/251705d0-004e-42da-9352-18a608e419ae" height="480px" width="720px">

## 4. Lighting 추가
- ambient, diffuse, specular 적용

<table border="1" width="100%">
  <tr>
    <th width="50%">미적용</th>
    <th width="50%">적용</th>
  </tr>
  <tr>
    <td align="center" valign="middle"><img src="https://github.com/user-attachments/assets/f86a9b18-9d48-4d10-91ad-982940fee3e0" width="500"></td>
    <td align="center" valign="middle"><img src="https://github.com/user-attachments/assets/45dfa126-d8ba-493f-9c58-b74d43c633fb" width="500"></td>
  </tr>
</table>

## 5. 카메라 구현
- 마우스의 위치 변화로 Yaw와 Pitch를 계산해 Front 벡터 수정

<img src="https://github.com/user-attachments/assets/6aac761f-65b9-4772-a419-6ac51074561a" height="480px" width="720px">


## 시연 영상

https://github.com/user-attachments/assets/bd787e34-f22e-438a-a503-69d0963d5d86


## 개선할 점
- C++을 처음 써봤기에 같이 공부하면서 하느라 코드 구조가 비교적 난잡
- Assimp 라이브러리 없이 직접 Sphere 구현
- 가능하면 스택말고 힙을 통해 메모리 관리 시도
- 궤적 부분에서 점말고 선으로 구현

