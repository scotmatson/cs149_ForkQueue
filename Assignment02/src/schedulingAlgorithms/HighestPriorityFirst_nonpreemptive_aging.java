package schedulingAlgorithms;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

import schedulingAlgorithms.util.Printer;

public class HighestPriorityFirst_nonpreemptive_aging {
	private final String name = "Aging HPF-NP";
    private ProcessQueue processQueue;
    private int[] finalTasksDone = {0, 0, 0, 0, 0};
    private float[] finalTurnaroundTime = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    private float[] finalWaitTime = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    private float[] finalResponseTime = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    private float finalTime = 0.0f;
    
    public HighestPriorityFirst_nonpreemptive_aging(ProcessQueue processQueue) {
        this.processQueue = processQueue;
    }

    /**
     * Highest Priority First (non-preemptive) with aging
     */
    public void runNonPreemptive() {
        for(int i = 1; i <= 5; i++) {
            // Variables needed for tracking progress of each run
            int clock = 0;
            int[] tasksDone = {0, 0, 0, 0, 0};
            int[] totalTasksDone = {0, 0, 0, 0, 0};
            float completionTime = 0.0f;
            float totalTime = 0.0f;
            float[] totalTurnaroundTime = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            float[] totalWaitTime = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            float[] totalResponseTime = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            List<List<Task>> scheduledTasks = new ArrayList<List<Task>>(5);
            scheduledTasks.add(0, new ArrayList<Task>());
            scheduledTasks.add(1, new ArrayList<Task>()); 
            scheduledTasks.add(2, new ArrayList<Task>()); 
            scheduledTasks.add(3, new ArrayList<Task>()); 
            scheduledTasks.add(4, new ArrayList<Task>());  

            // For each of 5 runs create a new process queue
            Task[] tasks = processQueue.generateProcesses(i);

            // Place task list into a queue for easier processing with HPF-NP
            Queue<Task> taskList = new LinkedList<Task>(Arrays.asList(tasks));
            
            // Comparator for the 4 priority queues.
            // Priority by arrival time with ties broken by run time
            Comparator<Task> c = new Comparator<Task>() {
                public int compare(Task t1, Task t2)
                {
                    int difference = t1.compareArrivalTime(t2.getArrivalTime());
                    if (difference == 0)
                    {
                        return (t1.compareRunTime(t2.getRunTime()));
                    }
                    return difference;
                }
            };
            // Create 4 Queues, one for each priority
            PriorityQueue<Task> readyQueueP1 = new PriorityQueue<>(10, c);
            PriorityQueue<Task> readyQueueP2 = new PriorityQueue<>(10, c);
            PriorityQueue<Task> readyQueueP3 = new PriorityQueue<>(10, c);
            PriorityQueue<Task> readyQueueP4 = new PriorityQueue<>(10, c);

            // Run the algorithm for all tasks
            while (!taskList.isEmpty() || !readyQueueP1.isEmpty() || !readyQueueP2.isEmpty()
                    || !readyQueueP3.isEmpty() || !readyQueueP4.isEmpty()) 
            {
                // Get the correct process to be scheduled based on priority
                // Tasks in readyQueue's have arrived by this time
                Task t;
                if (!readyQueueP1.isEmpty()) {
                    t = readyQueueP1.poll();
                }
                else if (!readyQueueP2.isEmpty()) {
                    t = readyQueueP2.poll();
                }
                else if (!readyQueueP3.isEmpty()) {
                    t = readyQueueP3.poll();
                }
                else if (!readyQueueP4.isEmpty()) {
                    t = readyQueueP4.poll();
                }
                else {
                    //No tasks have arrived yet so get the next task that has
                    t = taskList.poll();
                }

                //Update start and completion times for this process
                int startTime = Math.max((int)Math.ceil(t.getArrivalTime()), clock);
                if (startTime > 99) break;
                t.setStartTime(startTime);
                completionTime = startTime + t.getRunTime();
                t.setCompletionTime(completionTime);

                // Check the age of each priority queue to see if its been waiting for more than 5 quanta
                int[] wait = {0, 0, 0, 0, 0};
                //int waitP2 = 0;
                //int waitP3 = 0;
                //int waitP4 = 0;
                do {
                    // Only get waitTimes from queues that have processes in them otherwise keep waitTime at 0
                    wait[2] = (readyQueueP2.peek() != null) ? (startTime - readyQueueP2.peek().getArrivalTime()) : 0;
                    wait[3] = (readyQueueP3.peek() != null) ? (startTime - readyQueueP3.peek().getArrivalTime()) : 0;
                    wait[4] = (readyQueueP4.peek() != null) ? (startTime - readyQueueP4.peek().getArrivalTime()) : 0;

                    // Upgrade any tasks with waitTimes of more than 5 quanta
                    if (wait[2] >= 5)
                    {
                        readyQueueP1.add(readyQueueP2.poll());
                    }
                    if (wait[3] >= 5)
                    {
                        readyQueueP2.add(readyQueueP3.poll());
                    }
                    
                    if (wait[4] >= 5)
                    {
                        readyQueueP3.add(readyQueueP4.poll());
                    }
                } while (wait[2] >= 5 || wait[3] >= 5 || wait[4] >= 5);

                // Add in the correct ArrayList for completed tasks
                int thisP = t.getPriority();
                switch (thisP)
                {
                    case 1:
                        scheduledTasks.get(1).add(t);
                        tasksDone[1]++;
                        break;
                    case 2:
                        scheduledTasks.get(2).add(t);
                        tasksDone[2]++;
                        break;
                    case 3:
                        scheduledTasks.get(3).add(t);
                        tasksDone[3]++;
                        break;
                    default:
                        scheduledTasks.get(4).add(t);
                        tasksDone[4]++;
                        break;
                }
                
                // Update all completed tasks and clock
                scheduledTasks.get(0).add(t);
                tasksDone[0]++;
                clock = (int)Math.ceil(completionTime);

                // Add processes to the ready queue that have arrived by this time
                while (taskList.peek() != null && taskList.peek().getArrivalTime() <= clock) 
                {
                    Task next = taskList.poll();
                    
                    int nextP = next.getPriority();
                    switch (nextP)
                    {
                        case 1:
                            readyQueueP1.add(next);
                            break;
                        case 2:
                            readyQueueP2.add(next);
                            break;
                        case 3:
                            readyQueueP3.add(next);
                            break;
                        default:
                            readyQueueP4.add(next);
                            break;
                    }
                }

                // Variables for statistics for this process only
                float turnaroundTime = (completionTime - t.getArrivalTime());
                float waitTime = (turnaroundTime - t.getRunTime());
                int responseTime = (startTime - t.getArrivalTime());

                // Update totals at end of each run for each priority queue
                switch (thisP)
                {
                    case 1:
                        totalTurnaroundTime[1] += turnaroundTime;
                        totalWaitTime[1] += waitTime;
                        totalResponseTime[1] += responseTime;
                        totalTasksDone[1] = tasksDone[1];
                        break;
                    case 2:
                        totalTurnaroundTime[2] += turnaroundTime;
                        totalWaitTime[2] += waitTime;
                        totalResponseTime[2] += responseTime;
                        totalTasksDone[2] = tasksDone[2];
                        break;
                    case 3:
                        totalTurnaroundTime[3] += turnaroundTime;
                        totalWaitTime[3] += waitTime;
                        totalResponseTime[3] += responseTime;
                        totalTasksDone[3] = tasksDone[3];
                        break;
                    default:
                        totalTurnaroundTime[4] += turnaroundTime;
                        totalWaitTime[4] += waitTime;
                        totalResponseTime[4] += responseTime;
                        totalTasksDone[4] = tasksDone[4];
                        break;
                }
                
                // Update totals at end of each run for all processes
                totalTurnaroundTime[0] += turnaroundTime;
                totalWaitTime[0] += waitTime;
                totalResponseTime[0] += responseTime;
                totalTasksDone[0] = tasksDone[0];
                
                if (completionTime >= 99) 
                {
                    totalTime = completionTime; //time until last process is complete
                } 
                else 
                {
                    totalTime = 99;
                }
            }
            
            // Update final numbers needed for averages at each of 5 runs
            for (int p = 0; p < 5; p++) {
                finalTurnaroundTime[p] += totalTurnaroundTime[p];
                finalWaitTime[p] += totalWaitTime[p];
                finalResponseTime[p] += totalResponseTime[p];
                finalTasksDone[p] += totalTasksDone[p];
            }
            finalTime += totalTime;

            // Make a copy of the completed tasks to use in the time chart
            ArrayList<Task> tasksChart = new ArrayList<Task>(scheduledTasks.get(0));
            Printer.completedTasks(name, scheduledTasks.get(0), i);
            Printer.timeChart(name, tasksChart, i);
        }
        
        printFinalBenchmark();
    }
    
    /**
     * Prints out all calculated averages and throughput for
     *     a completed HighestPriorityFirst-NP simulation.
     */
    public void printFinalBenchmark()
    {
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY1 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime[1]/finalTasksDone[1]);
        System.out.println("Average Wait Time = " + finalWaitTime[1]/finalTasksDone[1]);
        System.out.println("Average Response Time = " + finalResponseTime[1]/finalTasksDone[1]);
        System.out.println("Throughput = " + finalTasksDone[1]/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY2 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime[2]/finalTasksDone[2]);
        System.out.println("Average Wait Time = " + finalWaitTime[2]/finalTasksDone[2]);
        System.out.println("Average Response Time = " + finalResponseTime[2]/finalTasksDone[2]);
        System.out.println("Throughput = " + finalTasksDone[2]/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY3 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime[2]/finalTasksDone[3]);
        System.out.println("Average Wait Time = " + finalWaitTime[3]/finalTasksDone[3]);
        System.out.println("Average Response Time = " + finalResponseTime[3]/finalTasksDone[3]);
        System.out.println("Throughput = " + finalTasksDone[3]/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("####### Final calculated averages and calculated throughput for HPF-NP PRIORITY4 ########");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime[4]/finalTasksDone[4]);
        System.out.println("Average Wait Time = " + finalWaitTime[4]/finalTasksDone[4]);
        System.out.println("Average Response Time = " + finalResponseTime[4]/finalTasksDone[4]);
        System.out.println("Throughput = " + finalTasksDone[4]/finalTime);
        System.out.println();
        
        System.out.println("\n######################################################################################");
        System.out.println("##### Final calculated averages and calculated throughput for HPF-NP ALL PROCESSES ######");
        System.out.println("######################################################################################");
        System.out.println("Average Turnaround Time = " + finalTurnaroundTime[0]/finalTasksDone[0]);
        System.out.println("Average Wait Time = " + finalWaitTime[0]/finalTasksDone[0]);
        System.out.println("Average Response Time = " + finalResponseTime[0]/finalTasksDone[0]);
        System.out.println("Throughput = " + finalTasksDone[0]/finalTime);
        System.out.println();
    }
}
