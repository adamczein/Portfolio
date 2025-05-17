// ---------------------------------------------------------    
// Assignment 3
// Written by: Adam El-Zein 40298143
// For COMP 249 Section U – Winter 2025
// A linked list that stores and manages tariff records.
// ---------------------------------------------------------

package part2;

import java.util.NoSuchElementException;

public class TariffList implements TariffPolicy {

    private class TariffNode {
        private Tariff tariff;
        private TariffNode next;

        public TariffNode() {
            this.tariff = null;
            this.next = null;
        }

        public TariffNode(Tariff tariff, TariffNode next) {
            this.tariff = tariff;
            this.next = next;
        }

        public TariffNode(TariffNode other) {
            this.tariff = (other.tariff != null) ? other.tariff.clone() : null;
            this.next = null;
        }

        public TariffNode clone() {
            return new TariffNode(this);
        }

        public Tariff getTariff() {
            return tariff;
        }

        public void setTariff(Tariff tariff) {
            this.tariff = tariff;
        }

        public TariffNode getNext() {
            return next;
        }

        public void setNext(TariffNode next) {
            this.next = next;
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (obj == null || getClass() != obj.getClass()) return false;

            TariffNode other = (TariffNode) obj;
            return (tariff == null) ? other.tariff == null : tariff.equals(other.tariff);
        }
    }

    private TariffNode head;
    private int size;

    public TariffList() {
        head = null;
        size = 0;
    }

    public TariffList(TariffList other) {
        this.head = null;
        this.size = 0;

        if (other.head == null) return;

        TariffNode otherCurrent = other.head;
        this.head = new TariffNode(otherCurrent.getTariff().clone(), null);

        TariffNode thisCurrent = this.head;
        otherCurrent = otherCurrent.getNext();

        while (otherCurrent != null) {
            thisCurrent.setNext(new TariffNode(otherCurrent.getTariff().clone(), null));
            thisCurrent = thisCurrent.getNext();
            otherCurrent = otherCurrent.getNext();
            this.size++;
        }

        this.size = other.size;
    }

    public void addToStart(Tariff tariff) {
        head = new TariffNode(tariff, head);
        size++;
    }

    public void insertAtIndex(Tariff tariff, int index) {
        if (index < 0 || index > size) {
            throw new NoSuchElementException("Invalid index: " + index);
        }

        if (index == 0) {
            addToStart(tariff);
            return;
        }

        TariffNode current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current.getNext();
        }

        current.setNext(new TariffNode(tariff, current.getNext()));
        size++;
    }

    public void deleteFromIndex(int index) {
        if (index < 0 || index >= size || head == null) {
            throw new NoSuchElementException("Invalid index: " + index);
        }

        if (index == 0) {
            deleteFromStart();
            return;
        }

        TariffNode current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current.getNext();
        }

        current.setNext(current.getNext().getNext());
        size--;
    }

    public void deleteFromStart() {
        if (head == null) return;

        head = head.getNext();
        size--;
    }

    public void replaceAtIndex(Tariff tariff, int index) {
        if (index < 0 || index >= size || head == null) return;

        TariffNode current = head;
        for (int i = 0; i < index; i++) {
            current = current.getNext();
        }

        current.setTariff(tariff);
    }

    public TariffNode find(String origin, String destination, String category) {
        TariffNode current = head;
        int iterations = 0;

        while (current != null) {
            iterations++;
            Tariff t = current.getTariff();

            boolean match1 = t.getOriginCountry().equalsIgnoreCase(origin) &&
                             t.getDestinationCountry().equalsIgnoreCase(destination) &&
                             t.getProductCategory().equalsIgnoreCase(category);

            boolean match2 = t.getDestinationCountry().equalsIgnoreCase(origin) &&
                             t.getOriginCountry().equalsIgnoreCase(destination) &&
                             t.getProductCategory().equalsIgnoreCase(category);

            if (match1 || match2) {
                System.out.println("Found after " + iterations + " iterations.");
                return current;
            }

            current = current.getNext();
        }

        System.out.println("Not found after " + iterations + " iterations.");
        return null;
    }

    public boolean contains(String origin, String destination, String category) {
        return find(origin, destination, category) != null;
    }

    @Override
    public String evaluateTrade(double proposedTariff, double minimumTariff) {
        if (proposedTariff >= minimumTariff) return "Accepted";
        if (proposedTariff >= minimumTariff * 0.8) return "Conditionally Accepted";
        return "Rejected";
    }

    public Tariff getTariff(String origin, String destination, String category) {
        TariffNode node = find(origin, destination, category);
        return (node != null) ? node.getTariff() : null;
    }

    public int getSize() {
        return size;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        TariffList other = (TariffList) obj;

        if (size != other.size) return false;

        TariffNode thisCurrent = head;
        TariffNode otherCurrent = other.head;

        while (thisCurrent != null) {
            if (!thisCurrent.equals(otherCurrent)) return false;
            thisCurrent = thisCurrent.getNext();
            otherCurrent = otherCurrent.getNext();
        }

        return true;
    }

    public void printAllTariffs() {
        TariffNode current = head;
        int count = 0;

        while (current != null) {
            Tariff t = current.getTariff();
            System.out.println("Tariff " + count + ": " +
                               t.getOriginCountry() + " -> " +
                               t.getDestinationCountry() + " -> " +
                               t.getProductCategory() + " = " +
                               t.getMinimumTariff() + "%");
            current = current.getNext();
            count++;
        }

        if (count == 0) {
            System.out.println("List is empty");
        }
    }
}
