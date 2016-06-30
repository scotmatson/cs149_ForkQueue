//package schedulingAlgorithms;
//
//import java.lang.reflect.Array;
//import java.util.ArrayList;
//import java.util.HashMap;
//
///**
// * Created by Natera on 6/29/16.
// */
//public class testShit {
//    public static void main(String[] args) {
//
//        // test tickQueue creation
//
//        public void agingCheck() {
//            Integer tickQueueCounter = 5;
//            ArrayList<Object> tickQueue = new ArrayList();
//            String testString = "testing";
//            Integer tickQueueSize = 12;
//            int tickCount = 0; // 100 Quanta
//
//
//            while (tickQueueCounter >= 0) {
//
//                //System.out.println("Counter number: " + tickQueueCounter);
//                //ArrayList<HashMap<String name, int value>> processes = new ArrayList<>(5);
//                ArrayList<HashMap<String, Integer>> processes = new ArrayList<>(5);
//                HashMap<String, Integer> nameAndPriority = new HashMap<>();
//                for (int i = 5; i > 0; i -= 1) {
//                    nameAndPriority.put(testString, 0); //Replace with Name and original priority
//                    processes.add(nameAndPriority);
//                }
//
//                Integer tick = tickQueueCounter;
//                tickQueue.add(0, processes);
//                tickQueue.add(0, tick);
//                tickQueueCounter -= 1;
//
//            }
//
//            System.out.println(tickQueue);
//            tickQueueCounter = 0;
//
//            //while (tickCount <= 100){
//
            for (Object tick : tickQueue) {
                Integer currentIndex = tickQueue.indexOf(tick);
                if (tick instanceof Integer) {
                    if ((Integer) tick == 5) {
                        //priorityBump(readyqueue, arraylist.getIndexOf(currentIndex + 1)
                        tickQueue.set(currentIndex, 0);
                    } else {
                        tickQueue.set(currentIndex, currentIndex + 1);
                    }


                }
//            }
//        }
//
//        public void addToAgingQueue(Task t, ArrayList tickQueue){
//
//        for(Object tick : tickQueue){
//            if (tick instanceof Integer){
//                if((Integer)tick == 0){
//                   Integer currentIndex = tickQueue.indexOf(tick);
//                    tickQueue.add(currentIndex + 1, t);
//                }
//            }
//        }
//    }
//
//}
//
