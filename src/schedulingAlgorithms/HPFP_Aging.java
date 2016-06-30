package schedulingAlgorithms;

import javafx.util.Pair;

import java.util.*;

//import HPFP_Queue;

/**
 * RoundRobin
 * This is not working correctly yet, feel free to modify it however you want
 * in order to get it working correctly
 * @author lord_tyler
 *
 */
public class HPFP_Aging {
    private ProcessQueue processQueue;
    private int finalTasksDone;
    private float finalTime;
    private float finalTurnaroundTime;
    private float finalWaitTime;
    private float finalResponseTime;
    private float priorityTotalTasks;

    /**
     * Constructor method.
     *
     * @param processQueue (ProcessQueue) : A specialized Queue used for
     *                     generating and sorting organized simulated processes.
     */
    public HPFP_Aging(ProcessQueue processQueue) {
        this.processQueue = processQueue;
        this.finalTasksDone = 0;
        this.finalTime = 0.0f;
        this.finalTurnaroundTime = 0.0f;
        this.finalWaitTime = 0.0f;
        this.finalResponseTime = 0.0f;
    }

    public void priorityBump(ArrayList<PriorityQueue<Task>> readyQueue, HashMap<Task, Integer> bumpThese) {
        Integer maxPriority = 1;
        Integer currentPriority;

        // iterate through the HashMap<Task, Integer>
        for (Map.Entry<Task, Integer> taskInt : bumpThese.entrySet()) {
            // get the currentPriority of the Task as listed in the HashMap (not the original priority
            // via task.getPriority() )
            currentPriority = taskInt.getValue();

            // If the Task increased tomaxPriority, then aging algo is finished with it. Remove from the tracking
            // HashMap
            if (currentPriority == maxPriority) {
                bumpThese.remove(taskInt);
            }

            // first, increment the priority counter for that Task in the HashMap
            // now, the readyQueue ArrayList is zero-indexed; if you want to add the task to the next-highest
            // priority queue, then you must use the -2 index in readyQueue
            // to remove a Task that was just bumped from its original priority queue, the index is -1

            else {
                readyQueue.get(currentPriority - 2).add(taskInt.getKey());
                readyQueue.get(currentPriority - 1).remove(taskInt.getKey());
                taskInt.setValue(taskInt.getValue() + 1);
            }
        }
    }

    /**
     * Runs a Highest Priority First (preemptive) with Aging algorithm g
     */
    public void runHPFP_Aging() {
        Integer priority1Tasks = 0;
        Integer priority2Tasks = 0;
        Integer priority3Tasks = 0;
        Integer priority4Tasks = 0;

        for (int i = 1; i <= 5; i++) {
            // Variables needed for tracking progress of each run
            int clock = 0;
            int tasksDone = 0;
            int totalTasksDone = 0;
            float completionTime = 0.0f;
            float totalTime = 0.0f;
            float totalTurnaroundTime = 0.0f;
            float totalWaitTime = 0.0f;
            float totalResponseTime = 0.0f;
            int priorityQueueCount = 4;
            int agingInterval = 5;

            ArrayList<Object> agingQueue = createAgingQueue(agingInterval);

            ArrayList<Task> scheduledTasks = new ArrayList<>();
            ArrayList<Task> completedTasks = new ArrayList<>();
            HPFP_Queue readyQueue = new HPFP_Queue(priorityQueueCount);
            Map<String, Float> remainingRunTimes = new HashMap<>();

            // For each of 5 runs create a new process queue
            Task[] tasks = processQueue.generateProcesses(i);
            // Sort task list by arrival time initially
            processQueue.sortByArrivalTime(tasks);
            // Place task list into a queue for processing with RR
            Queue<Task> taskList = new LinkedList<Task>(Arrays.asList(tasks));


            while (!taskList.isEmpty() || !readyQueue.isEmpty(readyQueue)) {

                agingCheck(readyQueue, agingQueue);

                //Add processes that have arrived to the ready queue
                while (!taskList.isEmpty() && taskList.peek().getArrivalTime() <= clock) {
                    Task t = taskList.poll();

                    readyQueue.addTask(readyQueue, t);
                    addToAgingQueue(t, agingQueue);
                }


                //Variables for statistics for this round only
                // changed sliceStartTime to startTime
                float turnaroundTime = 0.0f;
                float waitTime = 0.0f;
                float responseTime = 0.0f;
                float remainingTime = 0.0f;

                Task t;

                if (!readyQueue.isEmpty(readyQueue)) {
                    t = readyQueue.poll(readyQueue);
                    // t = readyQueuePoll();
                    if (t.getStartTime() == 0) {
                        t.setStartTime(Math.max((int) Math.ceil(t.getArrivalTime()), clock));
                    }

                    //Update if this is the first time seeing this process
                    if (!remainingRunTimes.containsKey(t.getName())) {
                        if (t.getStartTime() > 99) break;
                        responseTime = t.getStartTime() - t.getArrivalTime();
                        remainingTime = t.getRunTime() - 1;

                        //If process finishes in this time slice
                        if (remainingTime <= 0) {
                            // changed to t.getStartTime()
                            completionTime = t.getStartTime() + t.getRunTime();
                            t.setCompletionTime(completionTime);
                            tasksDone++;
                            completedTasks.add(t);
                            turnaroundTime = completionTime - t.getArrivalTime();
                            //Add wait time for all processes that have started but did not run in this slice
                            waitTime = remainingRunTimes.size() * t.getRunTime();
                        }
                        //Process did not finish yet but ran in this time slice
                        else {
                            //Add 1 quanta for all processes that have started but did not run in this slice
                            waitTime = remainingRunTimes.size();
                            //Add this process to remainingRunTimes and update remaining time
                            remainingRunTimes.put(t.getName(), remainingTime);
                            //Put back into queue at end of line
                            readyQueue.addTask(readyQueue, t);
                        }

                    }
                    //Update if the process has previously been started
                    else {
                        remainingTime = remainingRunTimes.get(t.getName()) - 1;
                        //If process finishes in this time slice
                        if (remainingTime <= 0) {
                            completionTime = t.getStartTime() + remainingRunTimes.get(t.getName());
                            t.setCompletionTime(completionTime);
                            tasksDone++;
                            completedTasks.add(t);
                            priorityTotalTasks += 1;
                            if (t.getPriority() == 4)
                            {
                                priority4Tasks += 1;
                            }
                            else if (t.getPriority() == 3) {
                                priority3Tasks += 1;
                            }
                            else if (t.getPriority() == 2) {
                                priority2Tasks += 1;
                            }
                            else
                            {
                                priority1Tasks += 1;
                            }
                            turnaroundTime = completionTime - t.getArrivalTime();
                            remainingRunTimes.remove(t.getName());
                            //Add wait time for all processes that have started but did not run in this slice
                            waitTime = remainingRunTimes.size() * (completionTime - t.getStartTime());
                        }
                        //Process did not finish yet but ran in this time slice
                        else {
                            //Add 1 quanta for all processes that have started but did not run in this slice
                            waitTime = remainingRunTimes.size() - 1; //Subtract 1 for the running process
                            //Update remaining time
                            remainingRunTimes.put(t.getName(), remainingTime);
                            //Put back into queue at end of line
                            readyQueue.addTask(readyQueue, t);
                        }
                    }
                }
                //There were no processes available to run in this slice
                else {
                    clock++;
                    if (completionTime >= 99) {
                        totalTime = completionTime; //time until last process is complete
                    } else {
                        totalTime = 99;
                    }
                    continue;
                }

                //Update the running schedule
                Task scheduled = (Task) t.clone();
                scheduled.setRunTime(1);
                scheduledTasks.add(scheduled);

                //Update totals at end of each run
                totalTurnaroundTime = totalTurnaroundTime + turnaroundTime;
                totalWaitTime = totalWaitTime + waitTime;
                totalResponseTime = totalResponseTime + responseTime;
                totalTasksDone = tasksDone;
                clock = t.getStartTime() + 1;
                if (completionTime >= 99) {
                    totalTime = completionTime; //time until last process is complete
                } else {
                    totalTime = 99;
                }
            }

            // Update final numbers needed for averages
            finalTurnaroundTime += totalTurnaroundTime;
            finalWaitTime += totalWaitTime;
            finalResponseTime += totalResponseTime;
            finalTime += totalTime;
            finalTasksDone += totalTasksDone;

            printCompletedTasks(completedTasks, i);
            printTimeChart(scheduledTasks, i);
        }
        printFinalBenchmark();
        System.out.println("priorityTotalTasks: " + priorityTotalTasks + "\t" + priority1Tasks);
        printPriorityStats(priority1Tasks, priority2Tasks, priority3Tasks, priority4Tasks, priorityTotalTasks);
    }

    public void printPriorityStats(Integer p1, Integer p2, Integer p3, Integer p4, float totalTasks) {
        float s1 = p1 / totalTasks;
        float s2 = p2 / totalTasks;
        float s3 = p3 / totalTasks;
        float s4 = p4 / totalTasks;

        System.out.println("Priority Stats:\n"
            + "\t\tP1:  " + s1
            + "\n\t\tP2:  " + s2
            + "\n\t\tP3:  " + s3
            + "\n\t\tP4:  " + s4);
    }
    /**
     * Prints out the stats for all completed tasks
     */
    public void printCompletedTasks(ArrayList<Task> scheduledTasks, int run) {
        System.out.println("\n########################################################################################");
        System.out.println("############ The following processes were completed for HPFP - Aging run " + run + " #####################");
        System.out.println("########################################################################################");
        while (!scheduledTasks.isEmpty()) {
            Task t = scheduledTasks.remove(0);
            System.out.println(t);
        }
    }


    public void printTimeChart(ArrayList<Task> tasksChart, int run) {
        System.out.println("\n############################################################");
        System.out.println("############ HPF Preemptive Time Chart for run " + run + " #####################");
        System.out.println("############################################################");
        new GanttChart(tasksChart);
    }

    /**
     * Prints out all calculated averages and throughput for
     * a completed FirstComeFirstServe simulation.
     */
    public void printFinalBenchmark() {
        System.out.println("\n#######################################################################################");
        System.out.println("############ Final calculated averages and calculated throughput for HPF - Aging #############");
        System.out.println("#######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime / finalTasksDone);
        System.out.println("Average Wait Time = " + finalWaitTime / finalTasksDone);
        System.out.println("Average Response Time = " + finalResponseTime / finalTasksDone);
        System.out.println("Throughput = " + finalTasksDone / finalTime);
    }

    public void agingCheck(ArrayList<PriorityQueue<Task>> readyQueue, ArrayList<Object> agingQueue) {
        for (Object tick : agingQueue)
        {
            Integer currentIndex = agingQueue.indexOf(tick);

            if (tick instanceof Integer)
            {
                try {
                    if ((Integer) tick == 5)
                    {
                        priorityBump(readyQueue, (HashMap<Task, Integer>) agingQueue.get(currentIndex + 1));
                        agingQueue.set(currentIndex, 0);
                    }
                    else
                    {
                        agingQueue.set(currentIndex, currentIndex + 1);
                    }
                }
                catch (ClassCastException e){}
            }
        }
    }

    public void addToAgingQueue(Task t, ArrayList<Object> agingQueue)
    {
        try {
            for (Object tick : agingQueue) {
                if (tick instanceof Integer) {
                    if ((Integer) tick == 0) {
                        Integer currentIndex = agingQueue.indexOf(tick);
                        agingQueue.add(currentIndex + 1, t);
                    }
                }
            }
        }
        catch (ConcurrentModificationException e) {}
    }

    public ArrayList<Object> createAgingQueue(Integer tickQueueCounter){
        Integer tickQueueSize = (tickQueueCounter * 2) + 2;
        ArrayList<Object> agingQueue = new ArrayList();

        while (tickQueueCounter >= 0) {

            //System.out.println("Counter number: " + tickQueueCounter);
            //ArrayList<HashMap<String name, int value>> processes = new ArrayList<>(5);
            HashMap<Task, Integer> taskInt = new HashMap<>();
            Integer tick = tickQueueCounter;
            agingQueue.add(0, taskInt);
            agingQueue.add(0, tick);
            tickQueueCounter -= 1;
        }

        return agingQueue;
    }
}
