#include "BoomDS.h"

StatusType BoomDS::AddCourse(int courseID, int numOfClasses)
{
    Course insert = Course(courseID, numOfClasses);

    //check memory allocation in AVL
    try
    {
        if (!courses.insertNode(courseID, insert))
        {
            // node already in tree
            return StatusType::FAILURE;
        }

        if (smallest_id == nullptr || courseID < smallest_id->getValue().get_id())
        {
            smallest_id = courses.findLastOfSearchPath(courseID);
        }
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType BoomDS::RemoveCourse(int courseID)
{
    try
    {
        std::shared_ptr<AVL_NODE<int, Course>> found_spot = courses.findLastOfSearchPath(courseID);
        if (!found_spot)
        {
            //empty course tree
            //empty course tree means failure (because the course doesn't exist), if we are in this function DS can't be null
            return StatusType::FAILURE;
        }

        //Course watched_course = found_spot->getValue();
        if (found_spot->getValue().get_id() != courseID)
        {
            //there is no such course
            return StatusType::FAILURE;
        }

        for (int i = 0; i < found_spot->getValue().getNumOfClasses(); i++)
        {
            lectures.deleteNode(found_spot->getValue().getLecture(i));
        }

        courses.deleteNode(courseID);

        most_watched = findMaxNode(lectures.getRoot());
        smallest_id = findMinNode(courses.getRoot());

        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType BoomDS::WatchClass(int courseID, int classID, int time)
{
    try
    {
        std::shared_ptr<AVL_NODE<int, Course>> found_spot = courses.findLastOfSearchPath(courseID);
        if (!found_spot)
        {
            //empty course tree
            //empty course tree means failure (because the course doesn't exist), if we are in this function DS can't be null
            return StatusType::FAILURE;
        }

        if (found_spot->getValue().get_id() != courseID)
        {
            return StatusType::FAILURE;
        }
        if (classID + 1 > found_spot->getValue().getNumOfClasses())
        {
            return StatusType::INVALID_INPUT;
        }

        ListNode<Lecture> *watched_lecture = (found_spot->getValue().getLectureArray())[classID];
        int old_time = watched_lecture->getValue()->getViews();
        Lecture key = Lecture(courseID, classID, old_time);
        lectures.deleteNode(key);
        watched_lecture->getValue()->addViews(time);
        Lecture *to_add = watched_lecture->getValue().get();
        if (!lectures.insertNode(*to_add, *to_add))
        {
            // some kind of error
            return StatusType::ALLOCATION_ERROR;
        }
        std::shared_ptr<AVL_NODE<Lecture, Lecture>> inserted = lectures.findLastOfSearchPath(*to_add);

        if (most_watched == nullptr || *to_add > most_watched->getValue())
        {
            most_watched = inserted;
        }

        if (!found_spot->getValue().get_watched(classID))
        {
            // since watched_course is a copy, and courses contain lectures as a list or pointer to list, changes don't stay after this function. need to use found_spot->getValue() but make sure
            removeFromUnwatched(found_spot->getValue(), watched_lecture);
            found_spot->getValue().set_watched(classID);
        }

        return StatusType::SUCCESS;
    }

    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType BoomDS::TimeViewed(int courseID, int classID, int *timeViewed)
{
    try
    {
        std::shared_ptr<AVL_NODE<int, Course>> found_spot = courses.findLastOfSearchPath(courseID);
        if (!found_spot)
        {
            //empty course tree
            //empty course tree means failure (because the course doesn't exist), if we are in this function DS can't be null
            return StatusType::FAILURE;
        }
        //Course watched_course = found_spot->getValue();
        if (found_spot->getValue().get_id() != courseID)
        {
            return StatusType::FAILURE;
        }
        if (classID + 1 > found_spot->getValue().getNumOfClasses())
        {
            return StatusType::INVALID_INPUT;
        }
        ListNode<Lecture> *watched_lecture = (found_spot->getValue().getLectureArray())[classID];
        *timeViewed = watched_lecture->getValue()->getViews();
        return StatusType::SUCCESS;
    }

    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType BoomDS::GetMostViewedClasses(int numOfClasses, int *courses, int *classes)
{
    try
    {
        int index = 0;
        reverseClimbLectures(most_watched, true, true, true, &index, courses, classes, numOfClasses);
        if (index < numOfClasses)
        {
            reverseClimbCourses(smallest_id, true, true, true, &index, courses, classes, numOfClasses);
        }
        if (index < numOfClasses)
        {
            // there are less than numofclasses lectures in system
            return StatusType::FAILURE;
        }
        return StatusType::SUCCESS;
    }

    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

void BoomDS::reverseClimbLectures(std::shared_ptr<AVL_NODE<Lecture, Lecture>> root, bool goUp, bool goRight, bool goLeft, int *index, int *courses, int *classes, int m)
{

    if (!root || *index >= m)
    {
        return;
    }
    // go right
    if (root->getRight() && goRight)
    {
        reverseClimbLectures(root->getRight(), false, true, true, index, courses, classes, m);
    }

    if (*index >= m)
    {
        return;
    }

    // save this node
    courses[*index] = root->getValue().getCourseID();
    classes[*index] = root->getValue().getLectureID();
    *index += 1;

    // go left
    if (root->getLeft() && goLeft)
    {
        reverseClimbLectures(root->getLeft(), false, true, true, index, courses, classes, m);
    }

    // go up
    if (root->getParent() && goUp)
    {
        // decide if this is the right or left child so we don't return here
        // add > operator to lecture, just activate the > operator of LectureKey
        if (root->getKey() > root->getParent()->getKey())
        {
            reverseClimbLectures(root->getParent(), true, false, true, index, courses, classes, m);
        }
        else
        {
            reverseClimbLectures(root->getParent(), true, true, false, index, courses, classes, m);
        }
    }
}

void BoomDS::reverseClimbCourses(std::shared_ptr<AVL_NODE<int, Course>> root, bool goUp, bool goRight, bool goLeft, int *index, int *courses, int *classes, int m)
{

    if (!root || *index >= m)
    {
        return;
    }
    // go left
    if (root->getLeft() && goLeft)
    {
        reverseClimbCourses(root->getLeft(), false, true, true, index, courses, classes, m);
    }

    if (*index >= m)
    {
        return;
    }

    ListNode<Lecture> *i = root->getValue().getUnwatchedRoot();

    while (*index < m && i)
    {
        courses[*index] = i->getValue()->getCourseID();
        classes[*index] = i->getValue()->getLectureID();
        *index += 1;
        i = i->getNext();
    }

    // go right
    if (root->getRight() && goRight)
    {

        reverseClimbCourses(root->getRight(), false, true, true, index, courses, classes, m);
    }

    // go up
    if (root->getParent() && goUp)
    {
        // decide if this is the right or left child so we don't return here
        if (root->getKey() > root->getParent()->getKey())
        {
            // this was the right child, don't go right again
            reverseClimbCourses(root->getParent(), true, false, true, index, courses, classes, m);
        }
        else
        {
            reverseClimbCourses(root->getParent(), true, true, false, index, courses, classes, m);
        }
    }
}

void BoomDS::removeFromUnwatched(Course &watched_course, ListNode<Lecture> *watched)
{
    if (!watched->getNext() && !watched->getPrev())
    {
        //only lecture
        watched_course.setUnwatchedRoot(nullptr);
    }
    else if (!watched->getNext())
    {
        //remove last
        watched->getPrev()->connectNext(nullptr);
    }
    else if (!watched->getPrev())
    {
        //remove first
        watched->getNext()->connectPrev(nullptr);
        watched_course.setUnwatchedRoot(watched->getNext());
    }
    else
    {
        //remove in the middle of the list
        watched->getPrev()->connectNext(watched->getNext());
        watched->getNext()->connectPrev(watched->getPrev());
    }

    // node should still exist because of the pointer in lecture_arr, so remove any connections
    watched->connectPrev(nullptr);
    watched->connectNext(nullptr);
}
