#include "ground.h"
using namespace std;
Ground::Ground() {}
QPair<QString, int> Ground::GroundWinner() {
    Card p1 = ground.front();
    ground.pop_front();
    Card p2 = ground.front();
    ground.pop_front();
    if (p1.get_type() != "flag" && p1.get_type() != "jack" &&
        p1.get_type() != "queen" && p1.get_type() != "skull") {

        if ((p2.get_type() == "flag" || p2.get_type() == "jack" ||
            p2.get_type() == "queen" || p2.get_type() == "skull")) {
            int score;
            if (p2.get_type() == "queen")
                score = 20;
            else {
                if (p2.get_type() == "skull")
                    score = 15;
                else
                    if (p2.get_type() == "jack")
                        score = 10;
                    else
                        score = 0;
            }
            QPair<QString, int> tmp(p2.getOwner(), score);
            return tmp;
        }
        else {
            if (p2.get_type() != p1.get_type()) {
                QPair<QString, int> tmp(p1.getOwner(), 0);
                return tmp;
            }
            else {
                if (p2.get_value() < p1.get_value()) {
                    QPair<QString, int> tmp(p1.getOwner(), 0);
                    return tmp;
                }
                else {
                    QPair<QString, int> tmp(p2.getOwner(), 0);
                    return tmp;
                }
            }
        }
    }
    else {
        if (p2.get_type() != "flag" && p2.get_type() != "jack" &&
            p2.get_type() != "queen" && p2.get_type() != "skull") {
            int score;
            if (p1.get_type() == "queen")
                score = 20;
            else {
                if (p1.get_type() == "skull")
                    score = 15;
                else
                    if (p1.get_type() == "jack")
                        score = 10;
                    else
                        score = 0;
            }
            QPair<QString, int> tmp(p1.getOwner(), score);
            return tmp;
        }
        else {
            if(p1.get_type() == "flag" && p2.get_type() == "flag")
                if (p1.get_value() > p2.get_value()) {
                    QPair<QString, int> tmp(p1.getOwner(), 0);
                    return tmp;
                }
                else {
                    QPair<QString, int> tmp(p2.getOwner(), 0);
                    return tmp;
                }
            else {
                if (p1.get_type() == "flag" ^ p2.get_type() == "flag") {
                    if (p1.get_type() == "flag") {
                        int score;
                        if (p2.get_type() == "queen")
                            score = 20;
                        else {
                            if (p2.get_type() == "skull")
                                score = 15;
                            else
                                if (p2.get_type() == "jack")
                                    score = 10;
                        }
                        QPair<QString, int> tmp(p2.getOwner(), score);
                        return tmp;
                    }
                    else {
                        int score;
                        if (p1.get_type() == "queen")
                            score = 20;
                        else {
                            if (p1.get_type() == "skull")
                                score = 15;
                            else
                                if (p1.get_type() == "jack")
                                    score = 10;
                        }
                        QPair<QString, int> tmp(p1.getOwner(), score);
                        return tmp;
                    }
                }
                else {
                    if(p1.get_type() == "queen")
                        if (p2.get_type() == "skull") {
                            QPair<QString, int> tmp(p2.getOwner(), 35);
                            return tmp;
                        }
                        else
                            if (p2.get_type() == "queen") {
                                QPair<QString, int> tmp(p1.getOwner(), 40);
                                return tmp;
                            }
                            else {
                                QPair<QString, int> tmp(p1.getOwner(), 30);
                                return tmp;
                            }
                    if(p1.get_type() == "skull")
                        if (p2.get_type() == "skull") {
                            QPair<QString, int> tmp(p1.getOwner(), 30);
                            return tmp;
                        }
                        else
                            if (p2.get_type() == "queen") {
                                QPair<QString, int> tmp(p1.getOwner(), 35);
                                return tmp;
                            }
                            else {
                                QPair<QString, int> tmp(p2.getOwner(), 25);
                                return tmp;
                            }
                    if(p1.get_type() == "jack")
                        if (p2.get_type() == "skull") {
                            QPair<QString, int> tmp(p1.getOwner(), 25);
                            return tmp;
                        }
                        else
                            if (p2.get_type() == "queen") {
                                QPair<QString, int> tmp(p2.getOwner(), 30);
                                return tmp;
                            }
                            else {
                                QPair<QString, int> tmp(p1.getOwner(), 20);
                                return tmp;
                            }
                }
            }
        }
    }
}
