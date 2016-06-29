package schedulingAlgorithms;

import java.util.ArrayList;

/**
 * Created by Natera on 6/29/16.
 */
public class testShit {
    public static void main(String[] args)
    {

        // test tickQueue creation
        Integer tickQueueCounter = 5;
        ArrayList<Object> tickQueue = new ArrayList();
        String testString = "process";
        Integer tickQueueSize = 12;

        while (tickQueueCounter >= 0)
        {
            ArrayList<String> processes = new ArrayList<>(5);
            for (int i = 5; i > 0; i -= 1)
            {
                processes.add(testString);
            }

            Integer tick = tickQueueCounter;
            tickQueue.add(0, processes);
            tickQueue.add(0, tick);
            tickQueueCounter -= 1;
        }

        for (Object thing : tickQueue)
        {
            tickQueueCounter -=1;
            if (tickQueuCounter % 2 == 0)
            {
                if (thing == 5) {
                    bump up all the prios;
                    thing = 0;
                }
                else
                {
                    thing += 1;

                }
                thing += 1
            };
        }


    }
}
