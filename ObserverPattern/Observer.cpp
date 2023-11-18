// 게임 프로그래밍 패턴의 관찰자 패턴 부분을 읽으며
// 작성하여 아래 내용만으로 구동하지 않습니다.


// class Observer
// {
//     public: virtual ~Observer(){}
//     virtual void onNotify(const Entity& entity, Event event) = 0;
// };

// class Achievements : public Observer
// {
//     public:
//         virtual void onNotify(const Entity& entity, Event event)
//         {
//             switch (event)
//             {
//                 case EVENT_ENTITY_FELL:
//                     if(entity.isHero() && heroIsOnBridge_)
//                     {
//                         unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
//                     }
//                     break;
//                     //그 외 다른 이벤트를 처리
//                     // heroIsOnBridge_ 값을 업데이트한다.
//             }
//         }

//     private:
//         void unlock(Achievement achievement)
//         {
//             //아직 업적이 잠겨 있다면 잠금 해제
//         }  
//         bool heroIsOnBridge_;
// };

// class Subject
// {
//     private:
//         Observer* observers_[MAX_OBSERVERS];
//         int numObservers_;

//     public:
//         void addObserver(Observer* observer)
//         {
//             //배열에 추가
//         }
//         void removeObserver(Observer* observer)
//         {
//             // 배열에서 제거
//         }
//         // 그 외 함수

//     protected:
//         void notify(const Entity& entity, Event event)
//         {
//             for(int i = 0; i < numObservers_; i++)
//             {
//                 observers_[i]->onNotify(entity, event);
//             }
//         }
// };

// class Physics : public Subject
// {
//     public:
//         void updateEntity(Entity& entity);
// };