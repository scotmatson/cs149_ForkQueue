package schedulingAlgorithms;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Created by danieltam on 6/27/16.
 */
public class HPFP_Queue<E> extends ArrayList<PriorityQueue<Task>>
{
    /**
	 * To make Eclipse shut up.
	 */
	private static final long serialVersionUID = 1L;

	public HPFP_Queue(int priorityQueueCount){
        while (priorityQueueCount > 0) {
            PriorityQueue<Task> priorityQueue = new PriorityQueue<>(10, new Comparator<Task>()
            {
                public int compare(Task t1, Task t2)
                {
                    return t1.compareArrivalTime(t2.getArrivalTime());
                }
            });
            this.add(priorityQueue);
            priorityQueueCount -= 1;
        }
    }

    public void printHPFP_Queue(HPFP_Queue<PriorityQueue<Task>> readyQueue)
    {
        for (PriorityQueue<Task> priorityQueue : readyQueue)
        {
            System.out.println("Priority Queue Stats:  \n");
            for (Task t : priorityQueue)
            {
                t.getPriority();
            }
        }
    }

    public boolean isEmpty(ArrayList<PriorityQueue<Task>> readyQueue)
    {
        for (PriorityQueue<Task> priorityQueue : readyQueue)
        {
            if (priorityQueue.isEmpty())
            {
                return true;
            }
        }
        return false;
    }

    public void addTask(ArrayList<PriorityQueue<Task>> priorityQueue, Task t) {
        priorityQueue.get(t.getPriority() - 1).add(t);
    }

    public Task poll(ArrayList<PriorityQueue<Task>> readyQueue){
        for (PriorityQueue<Task> priorityQueue : readyQueue){
            if(!priorityQueue.isEmpty()){
                try {
                    return priorityQueue.poll();
                }
                catch (NullPointerException e){

                }
            }
        }
        return null;
    }

}
